#include <windows.h>
#include <stdio.h>

// NOTE: windows.h must be compiled with STRICT defined

BOOL CALLBACK DesktopEnumProc(
                                LPTSTR lpszDesktop,	// name of a desktop
                                LPARAM lParam	// value specified in EnumDesktops call
                             )
{
    printf("\t%s\n", lpszDesktop);
    return TRUE;
};

//------------------------------------------------------------
BOOL CALLBACK EnumWindowStationProc(
                                    LPTSTR lpszWindowStation,	// name of a window station
                                    LPARAM lParam	            // value specified in EnumWindowStations call
                                   )
{
    printf( "%s\n", lpszWindowStation );

    HWINSTA hWinsta = OpenWindowStation( lpszWindowStation, FALSE, WINSTA_ENUMDESKTOPS );

    if (hWinsta)
    {
        EnumDesktops( hWinsta, DesktopEnumProc, 0 );
    }
    else
        printf("\tCannot open (%d)\n", GetLastError() );

    return TRUE;
};

void main()
{
    EnumWindowStations( EnumWindowStationProc, 0 ); 
};
