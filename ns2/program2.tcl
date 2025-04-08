#To create simulator object, trace file and nam file
set ns [new Simulator]
set nr [open thru.tr w]
$ns trace-all $nr
set nf [open thru.nam w]
$ns namtrace-all $nf

#Define procedure to clean up
proc finish { } {
     global ns nr nf
     $ns flush-trace
     close $nf
     close $nr
     exec nam thru.nam
     exit 0
}

#Creation of Nodes
for {set i 0} {$i < 6} {incr i} {
    set n$i [$ns node]
    }

#Creation of links
$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns simplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 3Mb 10ms DropTail
$ns simplex-link $n3 $n4 2Mb 10ms DropTail
$ns duplex-link $n3 $n5 2Mb 10ms DropTail

#Set up TCP connection
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $n5 $sink0

$ns connect $tcp0 $sink0

#Set up FTP over TCP connection
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ftp0 set packetSize_ 500
$ftp0 set interval_ 0.005

#Set up UDP connection
set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0

set null0 [new Agent/Null]
$ns attach-agent $n4 $null0

$ns connect $udp0 $null0

#Set up CBR over UDP connection
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005

#Schedule events for CBR and FTP agents
$ns at 0.1 "$ftp0 start"
$ns at 0.2 "$cbr0 start"
$ns at 4.5 "$ftp0 stop"
$ns at 4.5 "$cbr0 stop"
$ns at 5 "finish" 

#Run the simulation
$ns run


