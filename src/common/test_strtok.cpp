/* strtok example */
#include <stdio.h>
#include <string.h>
#include <string>

int main ()
{
      char str[] ="- This,, a sample string.";
        char * pch;
          printf ("Splitting string \"%s\" into tokens:\n",str);
            pch = strtok (str," ,.-");
              while (pch != NULL)
                    {
                            printf ("%s\n",pch);
                                pch = strtok (NULL, " ,.-");
                                  }

            std::string ss = "";
            printf("%s", ss.c_str());
                return 0;
}
 

