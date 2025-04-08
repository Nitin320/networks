
set ns [new Simulator]
set nr [open mytrace.tr w]
$ns trace-all $nr
set nf [open mynam.nam w]
$ns namtrace-all $nf

proc finish { } {
     global ns nr nf
     $ns flush-trace
     close $nf
     close $nr
     exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]


$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns simplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 2Mb 10ms DropTail

#Set up TCP connection
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $n3 $sink0

$ns connect $tcp0 $sink0

#Set up FTP over TCP connection
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

#Set up UDP connection
set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0

set null0 [new Agent/Null]
$ns attach-agent $n3 $null0

$ns connect $udp0 $null0

#Set up CBR over UDP connection
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0

#Schedule events for CBR and FTP agents
$ns at 1 "$cbr0 start"
$ns at 2 "$ftp0 start"
$ns at 8 "$cbr0 stop"
$ns at 9 "$ftp0 stop"
$ns at 10 "finish" 

#Run the simulation
$ns run


