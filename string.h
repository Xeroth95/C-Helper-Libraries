#ifndef STRING_H_GUARD
#define STRING_H_GUARD

extern char *byLineS(char *str, char *buf, int n);
extern char *byPerimeterS(char *str, char *buf, int n, char perimeter);
extern int byLineF(FILE *f, char *buf, int n);
extern int byPerimeterF(FILE *f, char *buf, int n, char perimeter);

#endif /* STRING_H_GUARD */
