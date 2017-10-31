  /****************************************************************************
    Implement the Boolean function F = AB’ + BC’D’
  ****************************************************************************/
  #include <Sim.h>                       // Interface to the "sim" package
  void simnet()                          // Function must be named "simnet"
  {
    Signal a, b, c, d, F;                // Switch and output objects
    Signal notb, notc, notd;
    Signal and1, and2;                   // Intermediate objects
    // Components and interconnections
    Switch ( SD("a0"), a, 'a' );             // Switch a controlled by ’a’ key
    Switch ( SD("b0"), b, 'b' );             // Switch b controlled by ’b’ key
    Switch ( SD("c0"), c, 'c' );             // Switch c controlled by ’c’ key
    Switch ( SD("d0"), d, 'd' );             // Switch d controlled by ’d’ key
    Not ( SD("b1"), b, notb );               // NOT gates   
    Not ( SD("c1"), c, notc );
    Not ( SD("d1"), d, notd );
    And ( SD("b2"), (a, notb), and1 );       // AND gates
    And ( SD("c2"), (b, notc, notd), and2 );
    Or ( SD("b3"), (and1, and2), F );        // OR gate
    Probe ( (SD("b4"), "F"), F );            // Probe
  }

