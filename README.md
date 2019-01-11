# Magnetic-Encoder
Function: magnetic encoder read-write coders.  
Notes :  
1. stm32C8t6 could write reg address to Mt6813, and MT6813 response with data back.  
2. both high 8bit and low 6 bit has been merged into one data as "Angle_HIGH"  
3. no parity check.  
  
!Need to be done:  
1. check magnetic signal (low byte [1] (0: magnet checked; 1: no magnet checked;)})  
2. parity check (according to the user manual Mt6813)  
3. the SYSTEM CLOCK seams not correct, should be improved.
