#include "serialport.h"

int connect(const char *port, unsigned baudRate, unsigned stopBits,
            bool canonical_mode, struct termios *originalTTYAttrs)
{
    int serial_port;
    struct termios tty;
    speed_t baud = baudRate;
    serial_port = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_port < 0) 
    {
		return -1;
    }

    memset(&tty, 0, sizeof tty);
    if (tcgetattr(serial_port, &tty) != 0) 
    {
		return -1;
    }

    cfsetospeed(&tty, baud);
    cfsetispeed(&tty, baud);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 50;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag |= 0;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) 
    {
		return -1;
    }
    return serial_port;
    return -1;
}

SerialPort::SerialPort(const char *port, unsigned baudRate, unsigned stopBits, bool canonical_mode)
{
    mFileDesc = connect(port, baudRate, stopBits, canonical_mode, &mOriginalTTYAttrs);

    if (mFileDesc == -1) 
    {
        std::cout << "Connect Error: " << strerror(errno) << std::endl;
    }
}

SerialPort::~SerialPort()
{
    if (mFileDesc == -1) {
        return;
    }

    tcflush(mFileDesc, TCIOFLUSH);
    close(mFileDesc);
}

int SerialPort::write(const char *buf, size_t nBytes)
{
    if (nBytes == 0) {
        return 0;
    }
    return ::write(mFileDesc, buf, nBytes);
}

int SerialPort::write(const std::string& string)
{
    size_t len = string.length();
    if (len == 0) {
        return 0;
    }
    return ::write(mFileDesc, string.c_str(), len);
}

int SerialPort::writebyte(const uint8_t *buf, size_t nBytes)
{
    int ret = 0;
     if (nBytes == 0) {
        return 0;
    }
    return ::write(mFileDesc, buf, nBytes);
}

uint8_t SerialPort::readbyte(void)
{
    uint8_t c;
    ::read(mFileDesc, &c, 1);
    return c;
}

int32_t SerialPort::Available(void)
{
    int32_t ret = 0;
    ioctl(mFileDesc, FIONREAD, &ret);
    return ret;
}
