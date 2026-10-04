#include <gtest/gtest.h>
#include <utility>
#include <cerrno>
#include "file_descriptor.h"


//  открыть /dev/null, проверить valid();
//  открыть несуществующий файл, проверить valid() == false и error() == ENOENT;
//  проверить перемещение (источник стал невалиден, приёмник владеет); 
// и главное — что после выхода из области видимости дескриптор закрыт, 
// через fcntl(fd, F_GETFD) == -1 && errno == EBADF.


TEST(FileDescriptorTest, OpensDevNull)          // valid() == true, get() >= 0
{
    FileDescriptor fd("/dev/null", O_RDONLY);
    ASSERT_NE(fcntl(fd.get(), F_GETFD), -1);
    EXPECT_TRUE(fd.valid());
    EXPECT_GE(fd.get(), 0);
}

TEST(FileDescriptorTest, FailsOnMissingFile)    // valid() == false, error() == ENOENT
{
    FileDescriptor fd("/noexist", O_RDONLY);
    EXPECT_FALSE(fd.valid());
    EXPECT_EQ(fd.get(), -1);
    EXPECT_EQ(fd.error(), ENOENT);
}

TEST(FileDescriptorTest, MoveTransfersOwnership) // источник невалиден, приёмник владеет
{
    FileDescriptor fd("/dev/null", O_RDONLY);
    ASSERT_NE(fcntl(fd.get(), F_GETFD), -1);
    int mem_fd = fd.get();
    FileDescriptor fd2 = std::move(fd);
    ASSERT_TRUE(fd2.valid());
    EXPECT_EQ(fd.get(), -1);
    ASSERT_NE(fcntl(fd2.get(), F_GETFD), -1);
    EXPECT_EQ(fd2.get(),mem_fd);
}

TEST(FileDescriptorTest, ClosesOnScopeExit)     // главный: fcntl после выхода из scope
{
int raw_fd{-1};
{
    FileDescriptor fd("/dev/null", O_RDONLY);
    raw_fd = fd.get();
    ASSERT_NE(fcntl(raw_fd, F_GETFD), -1);   // внутри scope дескриптор жив
}
EXPECT_EQ(fcntl(raw_fd, F_GETFD), -1);       // после выхода закрыт
EXPECT_EQ(errno, EBADF);
}

TEST(FileDescriptorTest, MoveAssignmentClosesOld) // старый дескриптор закрыт
{

    FileDescriptor a("/dev/null", O_RDONLY);
    ASSERT_NE(fcntl(a.get(), F_GETFD), -1);
    FileDescriptor b("/dev/null", O_RDONLY);
    ASSERT_NE(fcntl(b.get(), F_GETFD), -1);
    int fd_a{a.get()};
    int fd_b{b.get()};
    b = std::move(a);
    ASSERT_TRUE(b.valid());
    EXPECT_EQ(b.get(), fd_a);
    EXPECT_EQ(a.get(), -1);
    ASSERT_NE(fcntl(fd_a, F_GETFD), -1);
    EXPECT_EQ(fcntl(fd_b, F_GETFD), -1);
    EXPECT_EQ(errno, EBADF);
    
}

