
#ifndef HARDWARE_
#define HARDWARE_

/**************************************************************************
  Instructor-supplied data types, data objects, and functions
**************************************************************************/

typedef unsigned int signal4;
typedef unsigned int signal32;

/*-------------------------------------------------------------------------
  The control registers.
-------------------------------------------------------------------------*/

extern signal32 IR, CPSR;

/*-------------------------------------------------------------------------
  Function:  read_reg_file

  Purpose:   Fetch the contents of two registers from the register file.
    RS1 output port <== Reg[RS1 selection signal]
    RS2 output port <== Reg[RS2 selection signal]
-------------------------------------------------------------------------*/

void read_reg_file
(
  signal4,    /* RS1 selection signal */
  signal4,    /* RS2 selection signal */
  signal32*,  /* RS1 output port      */
  signal32*   /* RS2 output port      */
);

/*-------------------------------------------------------------------------
  Function:  write_reg_file

  Purpose:   Update the contents of one register in the register file.
    Reg[RD selection signal] <== RD input port
-------------------------------------------------------------------------*/

void write_reg_file
(
  signal4,    /* RD selection signal  */
  signal32    /* RD input port        */
);

#endif

