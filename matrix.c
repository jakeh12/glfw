#include "matrix.h"

void multiply(float r[], float a[], float b[])
{
  // row 0
  r[0] = a[0]*b[0] + a[4]*b[1] + a[8]*b[2] + a[12]*b[3];
  r[1] = a[1]*b[0] + a[5]*b[1] + a[9]*b[2] + a[13]*b[3];
  r[2] = a[2]*b[0] + a[6]*b[1] + a[10]*b[2] + a[14]*b[3];
  r[3] = a[3]*b[0] + a[7]*b[1] + a[11]*b[2] + a[15]*b[3];

  // row 1
  r[4] = a[0]*b[4] + a[4]*b[5] + a[8]*b[2] + a[12]*b[7];
  r[5] = a[1]*b[4] + a[5]*b[5] + a[9]*b[2] + a[13]*b[7];
  r[6] = a[2]*b[4] + a[6]*b[5] + a[10]*b[2] + a[14]*b[7];
  r[7] = a[3]*b[4] + a[7]*b[5] + a[11]*b[2] + a[15]*b[7];

  // row 2
  r[8] = a[0]*b[8] + a[4]*b[9] + a[8]*b[2] + a[12]*b[11];
  r[9] = a[1]*b[8] + a[5]*b[9] + a[9]*b[2] + a[13]*b[11];
  r[10] = a[2]*b[8] + a[6]*b[9] + a[10]*b[2] + a[14]*b[11];
  r[11] = a[3]*b[8] + a[7]*b[9] + a[11]*b[2] + a[15]*b[11];

  // row 3
  r[12] = a[0]*b[12] + a[4]*b[13] + a[8]*b[2] + a[12]*b[15];
  r[13] = a[1]*b[12] + a[5]*b[13] + a[9]*b[2] + a[13]*b[15];
  r[14] = a[2]*b[12] + a[6]*b[13] + a[10]*b[2] + a[14]*b[15];
  r[15] = a[3]*b[12] + a[7]*b[13] + a[11]*b[2] + a[15]*b[15];
}

void rotate(float m[], float x, float y, float z)
{
  float rot[16];
  rot[0] = cos(y)*cos(z);
  rot[1] = cos(z)*sin(x)*sin(y)-cos(x)*sin(z);
  rot[2] = cos(x)*cos(z)*sin(y)+sin(x)*sin(z);
  rot[3] = 0;

  rot[4] = cos(y)*sin(x);
  rot[5] = cos(x)*cos(z)+sin(x)*sin(y)*sin(z);
  rot[6] = cos(x)*sin(y)*sin(z)-cos(z)*sin(x);
  rot[7] = 0;

  rot[8] = -sin(y);
  rot[9] = cos(y)*sin(x);
  rot[10] = cos(x)*cos(y);
  rot[11] = 0;

  rot[12] = 0;
  rot[13] = 0;
  rot[14] = 0;
  rot[15] = 1;

  float m_copy[16];
  int i;
  for (i = 0; i < 16; i++) {
    m_copy[i] = m[i];
  }

  multiply(m, m_copy, rot);
}

void translate(float m[], float x, float y, float z)
{
  m[3] += x;
  m[7] += y;
  m[11] += z;
}
