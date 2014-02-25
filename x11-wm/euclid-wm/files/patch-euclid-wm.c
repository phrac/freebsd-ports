--- euclid-wm.c.orig	2014-02-25 11:44:15.164542491 -0600
+++ euclid-wm.c	2014-02-25 11:39:27.696609310 -0600
@@ -93,9 +93,9 @@
 
 
 //this is a hack
-FILE *popen(char *, char *);
+FILE *popen(const char *, const char *);
 int pclose (FILE *);
-char *tempnam(char *,char*);
+char *tempnam(const char *, const char*);
 
 
 #define BINDINGS 65 
