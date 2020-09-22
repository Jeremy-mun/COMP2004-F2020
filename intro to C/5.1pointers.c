
int main() {
  int x = 1, y = 2, z[10];
  int *ip;    /* ip is a pointer to int */
  z[0] = 5;

  ip = &x;    /* ip now points to x */
  y = *ip;    /* y is now 1 */
  *ip = 0;    /* x is now 0 */
  ip = &z[0]; /* ip now points to z[0] */

  return 0;
}
