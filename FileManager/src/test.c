#include <io.h>
#include <errno.h>
#include <sys/stat.h>
void maint()
{
	struct stat buf;
	int result, cm = _S_IFDIR;
	stat("c:\\Users\\All Users", &buf);

	result = _S_IFMT & buf.st_mode;

	if(result == cm)
	{
		result = 1;
	}
}