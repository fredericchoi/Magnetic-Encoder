# Magnetic-Encoder
magnetic encoder read-write coders 
stm32C8t6 could write reg address to Mt6813, and MT6813 response with data back.
both high 8bit and low 6 bit has been merged into one data as "Angle_HIGH"
no parity check.
need to be done:
check magnetic signal (low byte [1] (0: magnet checked; 1: no magnet checked;)})
parity check (according to the user manual Mt6813)
