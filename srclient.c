Algorithm for Selective Repeat Sender
Step 1: Start the program.

Step 2: Accept the total number of frames and the window size from the user.

Step 3: Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).

Step 4: Define the receiver address using the sockaddr_in structure.

Step 5: Attach a 2-second timeout to the socket using setsockopt() and SO_RCVTIMEO.

Step 6: Initialize variables: base = 0, next_seq = 0, and an array ack_received initialized to all zeros.

Step 7: Loop while base is less than total_packets.

Step 8: Inside the loop, send new frames. If next_seq < base + window_size, send the frame, increment next_seq, and repeat this step until the window limit is reached.

Step 9: Wait for an Acknowledgement using recvfrom().

Step 10: Check the return value of recvfrom():

If > 0 (Success): Mark the specific ACK in the array (ack_received[ack] = 1). Check if ack == base. If it is, use a while loop to increment base past all consecutively received ACKs (sliding the window).

If < 0 (Timeout): Display a timeout message. Loop from base to next_seq. If ack_received[i] == 0 (meaning no ACK was received for this specific frame), retransmit frame i.

Step 11: Repeat from Step 7 until all frames are successfully sent and acknowledged.

Step 12: Stop the program.