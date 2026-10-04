#ifndef FILEDESCRIPTOR_H
#define FILEDESCRIPTOR_H

#include <fcntl.h> //(open, флаги),
#include <unistd.h> //(close), 
#include <cerrno>

class FileDescriptor {
public:
    FileDescriptor(const char* path, int flags)
    :m_fd{::open(path, flags)} {if(m_fd < 0){ m_error= errno;}}

    ~FileDescriptor() {if(m_fd >= 0) ::close(m_fd);}

    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;

    FileDescriptor(FileDescriptor&& other) noexcept
    : m_fd{other.m_fd}
    {   
        other.m_fd = -1;
        m_error = other.m_error;
        other.m_error = 0;
    }


    FileDescriptor& operator=(FileDescriptor&& other) noexcept
    {
        if (this != &other)
        {
            if (m_fd >= 0){ ::close(m_fd);}
            m_fd = other.m_fd;
            other.m_fd = -1;
        }
        return *this;
    }

    int get() const {return m_fd;}
    bool valid() const { return m_fd >= 0;}
    int error() const {return m_error;}

private:
    int m_fd{-1};
    int m_error{0};
};

#endif

