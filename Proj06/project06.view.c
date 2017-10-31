
#include <stdio.h>

union sp_union
{
  float frep;
  unsigned irep;
};

void view_float( float );

int main()
{
  float x = -5.625;

  view_float( x );

  view_float( 7.25 );

  view_float( -0.125 );

  view_float( 0.1 );

  return 0;
}

void view_float( float value_to_view )
{
  union sp_union copy_of_value_to_view;

  copy_of_value_to_view.frep = value_to_view;

  printf( "%f (%08x)\n", copy_of_value_to_view.frep,
    copy_of_value_to_view.irep );
}

