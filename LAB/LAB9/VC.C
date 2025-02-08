Enter number of network nodes: 2
Enter the network connectivity matrix (0 for no connection, 1 for connection):
0 1 0 0

Enter number of network activities to simulate: 2

Simulation 1:
Enter node ID (0 to 1): 1
Select activity type:
1. Set packet count
2. Set failed attempts
Choice: 1
Enter value: 1500
Set packet count for Node 1 to 1500

Simulation 2:
Enter node ID (0 to 1): 0
Select activity type:
1. Set packet count
2. Set failed attempts
Choice: 2
Enter value: 8
Set failed attempts for Node 0 to 8

=== Starting Network Security Scan ===

BFS-based IDS Scan:
BFS Traversal Path: 0 ->
MALICIOUS NODE DETECTED: 0 (Packets: 0, Failed Attempts: 8)
1 ->
MALICIOUS NODE DETECTED: 1 (Packets: 1500, Failed Attempts: 0)
end

DFS-based IDS Scan:
DFS Traversal Path: 0 ->
MALICIOUS NODE DETECTED: 0 (Packets: 0, Failed Attempts: 8)
1 ->
MALICIOUS NODE DETECTED: 1 (Packets: 1500, Failed Attempts: 0)
end

=== Detailed Scan Results ===
Scan #1: Node 0 [MALICIOUS] detected by BFS
Scan #2: Node 1 [MALICIOUS] detected by BFS
Scan #3: Node 0 [MALICIOUS] detected by DFS
Scan #4: Node 1 [MALICIOUS] detected by DFS

=== Final Network Status ===
Node 0:
  Status: Malicious
  Packet Count: 0
  Failed Attempts: 8
Node 1:
  Status: Malicious
  Packet Count: 1500
  Failed Attempts: 0
Scan results saved to 'scan_results.log'.