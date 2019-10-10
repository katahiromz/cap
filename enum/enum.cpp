#include <windows.h>
#include <vfw.h>
#include <cstdio>

#pragma comment(lib, "vfw32.lib")
#define MAX_DRIVERS 10
#define MAX_NAME 128

int main(void)
{
    char name[MAX_NAME], ver[MAX_NAME];
    int id;
    for (id = 0; id < MAX_DRIVERS; id++)
    {
        if (!capGetDriverDescription(id, name, MAX_NAME, ver, MAX_NAME))
        {
            break;
        }
        printf("'%s': '%s'\n", name, ver);
    }
    return 0;
}
