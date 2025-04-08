#To create simulator object, trace file and nam file
set ns [new Simulator]
set nr [open routingLS.tr w]
$ns trace-all $nr
set nf [open routingLS.nam w]
$ns namtrace-all $nf

#Using routing protocol
$ns rtproto LS

#Define procedure to clean up
proc finish { } {
     global ns nr nf
     $ns flush-trace
     close $nf
     close $nr
     exec nam routingLS.nam
     exit 0
}

#Creation of Nodes
for {set i 0} {$i < 12} {incr i} {
    set n($i) [$ns node]
    }

#Creation of links
$ns duplex-link $n(0) $n(1) 1Mb 10ms DropTail
$ns duplex-link $n(1) $n(2) 1Mb 10ms DropTail
$ns duplex-link $n(2) $n(3) 1Mb 10ms DropTail
$ns duplex-link $n(3) $n(4) 1Mb 10ms DropTail
$ns duplex-link $n(4) $n(5) 1Mb 10ms DropTail
$ns duplex-link $n(5) $n(6) 1Mb 10ms DropTail
$ns duplex-link $n(6) $n(7) 1Mb 10ms DropTail
$ns duplex-link $n(7) $n(8) 1Mb 10ms DropTail
$ns duplex-link $n(8) $n(0) 1Mb 10ms DropTail  
$ns duplex-link $n(0) $n(9) 1Mb 10ms DropTail
$ns duplex-link $n(1) $n(10) 1Mb 10ms DropTail
$ns duplex-link $n(9) $n(11) 1Mb 10ms DropTail
$ns duplex-link $n(10) $n(11) 1Mb 10ms DropTail
$ns duplex-link $n(11) $n(5) 1Mb 10ms DropTail

#Set up UDP connection
set udp0 [new Agent/UDP]
$ns attach-agent $n(0) $udp0
set udp1 [new Agent/UDP]
$ns attach-agent $n(1) $udp1

set null0 [new Agent/Null]
$ns attach-agent $n(5) $null0
set null1 [new Agent/Null]
$ns attach-agent $n(5) $null1

$ns connect $udp0 $null0
$ns connect $udp1 $null1

#Set up CBR over UDP connection
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005


#Schedule events for CBR and FTP agents
$ns at 5.0 "$cbr0 start"
$ns at 5.0 "$cbr1 start"
$ns rtmodel-at 10.0 down $n(11) $n(5)
$ns rtmodel-at 30.0 up $n(11) $n(5)
$ns rtmodel-at 15.0 down $n(7) $n(6)
$ns rtmodel-at 20.0 up $n(7) $n(6)
$ns at 45.0 "$cbr0 stop"
$ns at 45.0 "$cbr1 stop"
$ns at 50.0 "finish" 

#Run the simulation
$ns run


