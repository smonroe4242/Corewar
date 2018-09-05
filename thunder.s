.name		"Thunder"
.comment	"After the lightning"

		ld		%64,r7
		ld		%32,r6
		ld		%16,r5
		ld		%8,r4
		ld		%4,r3
		sti		r1,%:loop,%1
		sti		r1,%:b,%1
		sti		r1,%:c,%1
		sti		r1,%:d,%1
		sti		r1,%:e,%1
1:      zjmp    %:b         #3  435 09 00 17
2:      zjmp    %:c         #3  438 09 00 26
3:      zjmp    %:d         #3  441 09 00 35
4:      zjmp    %:e         #3  444 09 00 44
5:      zjmp    %:f         #3  447 09 00 53
loop:   live    %1          #5  450 01 00 00 00 01
        fork    %:loop      #3  455 0c ff fb
b:      live    %1          #5  458 01 00 00 00 01
        fork    %:2         #3  463 0c ff e7
        add     r2,r6,r2    #5  466 04 54 02 06 02
        add     r15,r15,r15 #5  471 04 54 0f 0f 0f
c:      live    %1          #5  476 01 00 00 00 01
        fork    %:3         #3  481 0c ff d8
        add     r2,r5,r2    #5  484 04 54 02 05 02
        add     r15,r15,r15 #5  489 04 54 0f 0f 0f
d:      live    %1          #5  494 01 00 00 00 01
        fork    %:4         #3  499 0c ff c9
        add     r2,r4,r2    #5  502 04 54 02 04 02
        add     r15,r15,r15 #5  507 04 54 0f 0f 0f
e:      live    %1          #5  512 01 00 00 00 01
        fork    %:5         #3  517 0c ff ba
        add     r2,r3,r2    #5  520 04 54 02 03 02
        add     r15,r15,r15 #5  525 04 54 0f 0f 0f
f:      ldi     %13,r2,r16  #6  530 0a 94 00 0d 02 10
        ld      %0,r15      #7  536 02 90 00 00 00 00 0f
        sti     r16,%64,r2  #6  543 0b 64 10 00 40 02
        sti     r16,%122,r2 #6  549 0b 64 10 00 7a 02
        sti     r16,%180,r2 #6  555 0b 64 10 00 b4 02
        sti     r16,%238,r2 #6  561 0b 64 10 00 ee 02
        sti     r16,%296,r2 #6  567 0b 64 10 01 28 02
        sti     r16,%354,r2 #6  573 0b 64 10 01 62 02
        live    %42         #5  579 01 00 00 00 2a
        live    %42         #6  584 01 00 00 00 2a
        sti     r16,%402,r2 #6  590 0b 64 10 01 92 02
        sti     r16,%448,r2 #6  596 0b 64 10 01 c0 02
        zjmp    442         #3  602 09 01 ba
        live    %42         #5  605 01 00 00 00 2a