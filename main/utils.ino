#ifndef UTILS
#define UTILS

// converts character array
// to string and returns it
String convertToString(char *a, int size)
{
    int i;
    String s = "";
    for (i = 0; i < size; i++)
    {
        s = s + a[i];
    }
    return s;
}

#endif
