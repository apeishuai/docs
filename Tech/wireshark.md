![](/skins/bj2008/images/fire.gif) [wireshark](https://www.cnblogs.com/apeishuai/articles/18808526 "发布于 2025-04-03 22:51")

[filter expression](https://www.wireshark.org/docs/wsug_html_chunked/ChWorkBuildDisplayFilterSection.html)  
[filter example](https://wiki.wireshark.org/DisplayFilters)

tcp.port in {80}  
frame.number frame.len // frame就是数据包

# tshark

\-r xx.cap //read file  
\-e frame.time//field to print if Tfield is selected

capinfos xx.cap //包总览

tshark -r retrans.cap -q -z 'conv,ip' // 分析两个ip之间的流量

tshark -r nxx.cap -q -z 'conv,tcp' //分析每个会话之间的流量

tshark -r rsb2.cap -o tcp.calculate_timestamps:true -T fields -e frame.number -e frame.time_epoch -e ip.src -e ip.dst -e tcp.stream -e tcp.len -e tcp.analysis.initial_rtt -e tcp.time_delta //每个包的response time

tshark -r xx.cap -q -z 'export,note' //分析有问题的包、概览

tshark -r retrans.cap -q -z io,stat,1,”AVG(tcp.analysis.ack_rtt)tcp.analysis.ack_rtt”,”COUNT(tcp.analysis.retransmission) tcp.analysis.retransmission”,”COUNT(tcp.analysis.fast_retransmission) tcp.analysis.fast_retransmission”,”COUNT(tcp.analysis.duplicate_ack) tcp.analysis.duplicate_ack”,”COUNT(tcp.analysis.lost_segment) tcp.analysis.lost_segment”,”MIN(tcp.window_size)tcp.window_size” //分析rtt、丢包、deplicate等

tshark -r retrans.cap -q -z io,stat,5,”COUNT(tcp.analysis.retransmission) tcp.analysis.retransmission”,”COUNT(tcp.analysis.fast_retransmission) tcp.analysis.fast_retransmission”,”COUNT(tcp.analysis.duplicate_ack) tcp.analysis.duplicate_ack”,”COUNT(tcp.analysis.lost_segment) tcp.analysis.lost_segment” //分析丢包、duplicate ack

tshark -r ~/ali/metrics/tcpdump/rsb2.cap -q -z io,stat,1,”MIN(tcp.analysis.ack_rtt)tcp.analysis.ack_rtt”,”MAX(tcp.analysis.ack_rtt)tcp.analysis.ack_rtt”,”AVG(tcp.analysis.ack_rtt)tcp.analysis.ack_rtt” //分析rtt时间

tshark -r rsb-single2.cap -q -z io,stat,5,”COUNT(tcp.analysis.retransmission) tcp.analysis.retransmission”,”AVG(tcp.window_size) tcp.window_size”,”MAX(tcp.window_size) tcp.window_size”,”MIN(tcp.window_size) tcp.window_size” //计算window size

capinfos rsb2.cap↳

tshark -q -n -r rsb2.cap -z “conv,ip” 分析流量总况

tshark -q -n -r rsb2.cap -z “conv,tcp” 分析每一个连接的流量、rtt、响应时间、丢包率、重传率等等

editcap -c 100000 ./rsb2.cap rsb00.cap [//把大文件rsb2.cap按每个文件100000个package切成小文件](//xn--rsb2-p85fw35cupp5tf.xn--cap100000package-c69yga389aoa895ng75c932ai4e04rsa9054b)

# pyshark

https://kiminewt.github.io/pyshark/  
https://github.com/KimiNewt/pyshark  
https://pcapng.com/

Reading from a capture file:  
Reading from a live interface:  
Filtering packets:  
Accessing packet data:

cap = pyshark.FileCapture('/tmp/mycapture.cap') // read from file  
param keep_packets: Whether to keep packets after reading them via next(). Used to conserve memory when reading large caps.  
param input_file: Either a path or a file-like object containing either a packet capture file (PCAP, PCAP-NG..) or a TShark xml.  
param display_filter: A display (wireshark) filter to apply on the cap before reading it.  
param only_summaries: Only produce packet summaries, much faster but includes very little information  
param disable_protocol: Disable detection of a protocol (tshark > version 2)  
param decryption_key: Key used to encrypt and decrypt captured traffic.  
param encryption_type: Standard of encryption used in captured traffic (must be either 'WEP', 'WPA-PWD', or 'WPA-PWK'. Defaults to WPA-PWK.  
param tshark_path: Path of the tshark binary

capture = pyshark.LiveCapture(interface='eth0') // read from living xx  
param interface: Name of the interface to sniff on. If not given, takes the first available.  
param bpf_filter: BPF filter to use on packets.  
param display_filter: Display (wireshark) filter to use.  
param only_summaries: Only produce packet summaries, much faster but includes very little information  
param disable_protocol: Disable detection of a protocol (tshark > version 2)  
param decryption_key: Key used to encrypt and decrypt captured traffic.  
param encryption_type: Standard of encryption used in captured traffic (must be either 'WEP', 'WPA-PWD', or 'WPA-PWK'. Defaults to WPA-PWK).  
param tshark_path: Path of the tshark binary  
param output_file: Additionally save captured packets to this file.

capture = pyshark.LiveRingCapture(interface='eth0') //read from a living interface using a ring buffer  
param ring_file_size: Size of the ring file in kB, default is 1024  
param num_ring_files: Number of ring files to keep, default is 1  
param ring_file_name: Name of the ring file, default is /tmp/pyshark.pcap  
param interface: Name of the interface to sniff on. If not given, takes the first available.  
param bpf_filter: BPF filter to use on packets.  
param display_filter: Display (wireshark) filter to use.  
param only_summaries: Only produce packet summaries, much faster but includes very little information  
param disable_protocol: Disable detection of a protocol (tshark > version 2)  
param decryption_key: Key used to encrypt and decrypt captured traffic.  
param encryption_type: Standard of encryption used in captured traffic (must be either 'WEP', 'WPA-PWD', or 'WPA-PWK'. Defaults to WPA-PWK).  
param tshark_path: Path of the tshark binary  
param output_file: Additionally save captured packets to this file.

capture = pyshark.RemoteCapture('192.168.1.101', 'eth0') //read from a remote interface  
param remote_host: The remote host to capture on (IP or hostname). Should be running rpcapd.  
param remote_interface: The remote interface on the remote machine to capture on. Note that on windows it is not the device display name but the true interface name (i.e. \\Device\\NPF_..).  
param remote_port: The remote port the rpcapd service is listening on  
param bpf_filter: A BPF (tcpdump) filter to apply on the cap before reading.  
param only_summaries: Only produce packet summaries, much faster but includes very little information  
param disable_protocol: Disable detection of a protocol (tshark > version 2)  
param decryption_key: Key used to encrypt and decrypt captured traffic.  
param encryption_type: Standard of encryption used in captured traffic (must be either 'WEP', 'WPA-PWD', or 'WPA-PWK'. Defaults to WPA-PWK).  
param tshark_path: Path of the tshark binary

pcapng文件构成：

Section Header Block:  
Block Type (4 bytes) = 0x0a0d0d0a  
Block Length (4 bytes)  
Byte-Order Magic (4 bytes) = 0x1a2b3c4d  
Major Version (2 bytes) = 0x0001  
Minor Version (2 bytes) = 0x0000  
Section Length (8 bytes) = 0xffffffffffffffff  
Options (variable length)  
Block Length (redundant 4 byte value)

Interface Description Block:  
contains metadata about the network interface used to capture the packets  
Block Type (4 bytes) = 0x00000001  
Block Total Length (4 bytes)  
Link Type (2 bytes)  
Reserved (2 bytes) = 0x0000  
Snap Length (4 bytes)  
Options (variable length)  
Block Total Length (redundant 4 byte value)

Packet Blocks:  
be used to store packets, which are “Packet Block”, “Simple Packet Block” (SPB) and “Enhanced Packet Block” (EPB), only EPB used in xxx  
Block Type (4 bytes) = 0x00000006  
Block Total Length (4 bytes)  
Interface ID (4 bytes)  
Timestamp Upper (4 bytes)  
Timestamp Lower (4 bytes)  
Captured Packet Length (4 bytes)  
Original Packet Length (4 bytes)  
Packet Data (variable length)  
Options (variable length)  
Block Total Length (redundant 4 byte value)