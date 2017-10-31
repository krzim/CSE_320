
/******************************************************************************
  Project #4 skeleton
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, Signal, Signal );


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
	Signal Init, Clock, w, x, y, z;
	
	// Pulsers
    Pulser ((SD("2a"), "Clock"),  Clock, 'c', 10000); 
	Pulser ((SD("3a"), "Initialize"),  Init, 'i', 10000); 

	circuits( SD("1b-4b"), Init, Clock, w, x, y, z );

	// Probes
	Probe ( (SD("1c"), "w"), w );
	Probe ( (SD("2c"), "x"), x );
	Probe ( (SD("3c"), "y"), y );
	Probe ( (SD("4c"), "z"), z );

}


/******************************************************************************
  Function "circuits" -- implementation of student circuits
******************************************************************************/

void circuits( SD sd, Signal Init, Signal Clock, 
  Signal w, Signal x, Signal y, Signal z )
{
  Module( (sd, "circuits"), (Init, Clock), (w, x, y, z) );

  	// NOT Signals
	Signal notw, notx, noty, notz;
	
	// Out Signals
	Signal W, X, Y, Z;
	
	// AND Signals
	Signal notw_notx_notz, w_noty_notz, notw_noty_z, 
	x_noty, y_z, w_notz;

	// DFFs
	Dff( SD(sd,"1d"), ( Init, W, Clock, Zero ), w );
	Dff( SD(sd,"1d"), ( Zero, X, Clock, Init ), x );
	Dff( SD(sd,"1d"), ( Init, Y, Clock, Zero ), y );
	Dff( SD(sd,"1d"), ( Zero, Z, Clock, Init ), z );

	// NOTs
	Not( SD(sd, "1d"), w, notw);
	Not( SD(sd, "1d"), x, notx);
	Not( SD(sd, "3d"), y, noty);
	Not( SD(sd, "4d"), z, notz);

	// ANDs
	And( SD(sd, "5d"), (notw, notx, notz), notw_notx_notz );
	And( SD(sd, "5d"), (w, noty, notz), w_noty_notz );
	And( SD(sd, "5d"), (notw, noty, z), notw_noty_z );
	And( SD(sd, "5d"), (x, noty), x_noty );
	And( SD(sd, "5d"), (y, z), y_z );
	And( SD(sd, "5d"), (w, notz), w_notz );
	And( SD(sd, "5d"), (y, y), Z );
	
	// ORs
	Or( SD(sd, "5d"), (notw_notx_notz, x_noty, y_z), W );
	Or( SD(sd, "5d"), (w_noty_notz, notw_noty_z), X );
	Or( SD(sd, "5d"), (w_notz, x_noty), Y );
	}

