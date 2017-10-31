
/******************************************************************************
  Project #3 skeleton
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, 
	Signal, Signal, Signal, Signal, Signal, Signal, Signal, Signal );


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
	Signal w, x, y, z, Present, a, b, c, d, e, f, g, reset, incrmnt,
		   notreset;

	 //Code to generate four input signals
  
	//Switch ( SD("1b"), w, 'w' );
	//Switch ( SD("2b"), x, 'x' );
	//Switch ( SD("3b"), y, 'y' );
	//Switch ( SD("4b"), z, 'z' );

    Pulser ((SD("2a"), "Reset count (r)"),  reset, 'r', 10000);
	Pulser ((SD("3a"), "Increment (i)"), incrmnt, 'i', 10000);
	
	// Compliment reset as it's active low
	Not( SD("2a"), reset, notreset); 
	
	Counter ((SD("1b-4b"), "4-bit counter"), (notreset, incrmnt),
			 (w, x, y, z));

	circuits( SD("1d-4d"), w, x, y, z, Present, a, b, c, d, e, f, g);

	// Code to display eight output signals

	Probe ( (SD("1e"), "Present"), Present );
	Probe ( (SD("1g-1i"), "a"), a );
	Probe ( (SD("1i-3i"), "b"), b );
	Probe ( (SD("3i-5i"), "c"), c );
	Probe ( (SD("5g-5i"), "d"), d );
	Probe ( (SD("3g-5g"), "e"), e );
	Probe ( (SD("1g-3g"), "f"), f );
	Probe ( (SD("3g-3i"), "g"), g );
  
}


/******************************************************************************
  Function "circuits" -- implementation of student circuits

  Do not alter the interface -- function "circuits" must receive four
  signals as inputs and return eight signals as outputs.
******************************************************************************/

void circuits( SD sd, Signal w, Signal x, Signal y, Signal z, 
	Signal Present, Signal a, Signal b, Signal c, Signal d, Signal e,
	Signal f, Signal g )    
{
	Module( (sd, "circuits"), (w, x, y, z), (Present, a, b, c, d, e, f, g) );

	// Declarations for auxiliary Signals
	
	// NOT's
	Signal notw, notx, noty, notz;
	
	// AND's
	Signal notw_notx_z, notw_x_notz, w_notx_notz, notx_noty, 
	notx_noty_notz, notw_y, w_notx, notw_notx, x_noty, w_noty, y_notz,
	noty_notz, y_z, notw_x ;

	// Circuit implementation (Not, And, Or gates)
	
	// NOT's
	Not( SD(sd, "1d"), w, notw);
	Not( SD(sd, "2d"), x, notx);
	Not( SD(sd, "3d"), y, noty);
	Not( SD(sd, "4d"), z, notz);
	
	// AND's
	And( SD(sd, "5d"), (notw, notx, z), notw_notx_z );
	And( SD(sd, "5d"), (notw, x, notz), notw_x_notz );
	And( SD(sd, "5d"), (w, notx, notz), w_notx_notz );
	And( SD(sd, "5d"), (notx, noty), notx_noty );
	And( SD(sd, "5d"), (notx, noty, notz), notx_noty_notz );
	And( SD(sd, "5d"), (notw, y), notw_y );
	And( SD(sd, "5d"), (w, notx), w_notx );
	And( SD(sd, "5d"), (notw, notx), notw_notx );
	And( SD(sd, "5d"), (x, noty), x_noty );
	And( SD(sd, "5d"), (w, noty), w_noty );
	And( SD(sd, "5d"), (y, notz), y_notz );
	And( SD(sd, "5d"), (noty, notz), noty_notz );
	And( SD(sd, "5d"), (y, z), y_z );
	And( SD(sd, "5d"), (notw, x), notw_x );
	
	// OR's
	
	Or( SD(sd, "5d"), 
	   (notw_notx_z, notw_x_notz, w_notx_notz, notx_noty), Present );
	Or( SD(sd, "5d"), (notx_noty_notz, notw_y, w_notx), a );
	Or( SD(sd, "5d"), (notw_notx, x_noty, w_notx), b );
	Or( SD(sd, "5d"), (One), c );
	Or( SD(sd, "5d"), (notw_y, w_noty, notx_noty_notz), d );
	Or( SD(sd, "5d"), (notx_noty_notz, y_notz), e );
	Or( SD(sd, "5d"), (w_notx, noty_notz, y_notz), f );
	Or( SD(sd, "5d"), (y_z, notw_x, w_notx), g );
}	

