Closet-Door-Lightswitch
=======================

A project that detects when a closet door is opened and then automatically turns on the closet lighting. It is controlled by a TI MSP430G2001 microcontroller that is powered from 3.3V DC derived from 120V AC line voltage. Reed switches and magnets on the doors of the closet act as a switch so the microcontroller can detect when the door is opened and turn on an LED indicating that one of the doors is open. If at least one of the doors is open, the microcontroller switches a relay to turn on an overhead light. The light is automatically shut off after five minutes if the doors are not shut.

Schematic files created using Cadsoft EAGLE 6.2.0.
Code compiled using Texas Instruments Code Composer Studio Core Edition 4.2.5.

This work is licensed under a Creative Commons Attribution 3.0 Unported License.
