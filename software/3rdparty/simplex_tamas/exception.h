// Added by Changkyu Song (WIN -> LINUX)
#ifdef __gnu_linux__
  #include <inttypes.h>
//  typedef int __int64;
#define __int64 int
#endif
//~Added by Changkyu Song (WIN -> LINUX)


#define FE_MESSAGE_BUFFER_SIZE 1024

/**
 * Exception class with printf like text formatting
 * capabilities, using variable argument list.
 */
class FException {
private:
	char error_msg[FE_MESSAGE_BUFFER_SIZE];
	unsigned __int64 error_code;

protected:

public:
	FException(char* error_msg, ...);
	FException(unsigned __int64 error_code, char* error_msg, ...);

	void Print();
	unsigned __int64 getErrorCode();
	char *getMessage();
};
