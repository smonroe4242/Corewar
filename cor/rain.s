.name		"The Storm"
.comment	"Dread Code"

		ld		%64,r7		#7	0	02 90 00 00 00 40 07
		ld		%32,r6		#7	7	02 90 00 00 00 20 06
		ld		%16,r5		#7	14	02 90 00 00 00 10 05
		ld		%8,r4		#7	21	02 90 00 00 00 08 04
		ld		%4,r3		#7	28	02 90 00 00 00 04 03
		st		r1,424		#5	35	03 70 01 01 a8
		st		r16,-4		#5	40	03 70 10 ff fc
		st		r1,432		#5	45	03 70 01 01 b0
		st		r16,-4		#5	50	03 70 10 ff fc
		st		r1,440		#5	55	03 70 01 01 b8
		st		r16,-4		#5	60	03 70 10 ff fc
		st		r1,448		#5	65	03 70 01 01 c0
		st		r16,-4		#5	70	03 70 10 ff fc
		st		r1,376		#5	75	03 70 01 01 78
		st		r16,-4		#5	80	03 70 10 ff fc
		st		r1,73		#5	85	03 70 01 00 49
		st		r16,-4		#5	90	03 70 10 ff fc
		st		r1,55		#5	95	03 70 01 00 37
		st		r16,-4		#5	100	03 70 10 ff fc
		ld		%0,r15		#7	105	02 90 00 00 00 00 0f
		st		r1,468		#5	112	03 70 01 01 d4
		st		r16,-4		#5	117	03 70 10 ff fc
		st		r1,463		#5	122	03 70 01 01 cf
		st		r16,-4		#5	127	03 70 10 ff fc
		fork	318			#3	132	0c 01 3e
		ld		%0,r2		#7	135	02 90 00 00 00 00 02
		ld		%0,r16		#7	142	02 90 00 00 00 00 10
		live	%42			#5	149	01 00 00 00 2a
		fork	-5			#3	154	0c ff fb
wall:	live	%4902343	#5	157	01 00 4a cd c7
		st		r2,-33		#5	162	03 70 02 ff df
		st		r2,-42		#5	167	03 70 02 ff d6
		st		r2,-51		#5	172	03 70 02 ff cd
		st		r2,-60		#5	177	03 70 02 ff c4
		st		r2,-69		#5	182	03 70 02 ff bb
		st		r2,-78		#5	187	03 70 02 ff b2
		st		r2,-87		#5	192	03 70 02 ff a9
		st		r2,-96		#5	197	03 70 02 ff a0
		st		r2,-105		#5	202	03 70 02 ff 97
		st		r2,-114		#5	207	03 70 02 ff 8e
		st		r2,-123		#5	212	03 70 02 ff 85
		st		r2,-132		#5	217	03 70 02 ff 7c
		st		r2,-141		#5	222	03 70 02 ff 73
		st		r2,-150		#5	227	03 70 02 ff 6a
		st		r2,-159		#5	232	03 70 02 ff 61
		st		r2,-168		#5	237	03 70 02 ff 58
		st		r2,-177		#5	242	03 70 02 ff 4f
		st		r2,-186		#5	247	03 70 02 ff 46
		st		r2,-195		#5	252	03 70 02 ff 3d
		st		r2,-204		#5	257	03 70 02 ff 34
		st		r2,-213		#5	262	03 70 02 ff 2b
		st		r2,-222		#5	267	03 70 02 ff 22
		st		r2,-231		#5	272	03 70 02 ff 19
		st		r2,-240		#5	277	03 70 02 ff 10
		st		r2,-249		#5	282	03 70 02 ff 07
		st		r2,-258		#5	287	03 70 02 fe fe
		st		r2,-267		#5	292	03 70 02 fe f5
		st		r2,-276		#5	297	03 70 02 fe ec
		st		r2,-285		#5	302	03 70 02 fe e3
		st		r2,-294		#5	307	03 70 02 fe da
		st		r2,-303		#0	312	53 70 02 fe d1
		st		r2,-312		#5	317	03 70 02 fe c8
		st		r2,-321		#5	322	03 70 02 fe bf
		st		r2,-330		#5	327	03 70 02 fe b6
		st		r2,-339		#5	332	03 70 02 fe ad
		st		r2,-348		#5	337	03 70 02 fe a4
		st		r2,-357		#5	342	03 70 02 fe 9b
		st		r2,-366		#5	347	03 70 02 fe 92
		st		r2,-375		#5	352	03 70 02 fe 89
		st		r2,-384		#5	357	03 70 02 fe 80
		st		r2,-393		#5	362	03 70 02 fe 77
		st		r2,-402		#5	367	03 70 02 fe 6e
		st		r2,-411		#5	372	03 70 02 fe 65
		st		r2,-420		#5	377	03 70 02 fe 5c
		st		r2,-429		#5	382	03 70 02 fe 53
		st		r2,-438		#5	387	03 70 02 fe 4a
		st		r2,-447		#5	392	03 70 02 fe 41
		st		r2,-456		#5	397	03 70 02 fe 38
		st		r2,-465		#5	402	03 70 02 fe 2f
		st		r2,-474		#5	407	03 70 02 fe 26
		st		r2,-483		#5	412	03 70 02 fe 1d
		st		r2,-492		#5	417	03 70 02 fe 14
		st		r2,-501		#5	422	03 70 02 fe 0b
		st		r2,-510		#5	427	03 70 02 fe 02
		zjmp	%:wall		#3	432	09 fe ed
		zjmp	23			#3	435	09 00 17
		zjmp	38			#3	438	09 00 26
		zjmp	53			#3	441	09 00 35
		zjmp	68			#3	444	09 00 44
		zjmp	83			#3	447	09 00 53
		live	%1			#5	450	01 00 00 00 01
		fork	-5			#3	455	0c ff fb
a:		live	%1			#5	458	01 00 00 00 01
		fork	-25			#3	463	0c ff e7
		add		r2,r6,r2	#5	466	04 54 02 06 02
		add		r15,r15,r15	#5	471	04 54 0f 0f 0f
		live	%1			#5	476	01 00 00 00 01
		fork	-40			#3	481	0c ff d8
		add		r2,r5,r2	#5	484	04 54 02 05 02
		add		r15,r15,r15	#5	489	04 54 0f 0f 0f
		live	%1			#5	494	01 00 00 00 01
		fork	-55			#3	499	0c ff c9
		add		r2,r4,r2	#5	502	04 54 02 04 02
		add		r15,r15,r15	#5	507	04 54 0f 0f 0f
		live	%1			#5	512	01 00 00 00 01
		fork	-70			#3	517	0c ff ba
		add		r2,r3,r2	#5	520	04 54 02 03 02
		add		r15,r15,r15	#5	525	04 54 0f 0f 0f
		ldi		%13,r2,r16	#6	530	0a 94 00 0d 02 10
		ld		%0,r15		#7	536	02 90 00 00 00 00 0f
		sti		r16,%64,r2	#6	543	0b 64 10 00 40 02
		sti		r16,%122,r2	#6	549	0b 64 10 00 7a 02
		sti		r16,%180,r2	#6	555	0b 64 10 00 b4 02
		sti		r16,%238,r2	#6	561	0b 64 10 00 ee 02
		sti		r16,%296,r2	#6	567	0b 64 10 01 28 02
		sti		r16,%354,r2	#6	573	0b 64 10 01 62 02
		live	%42			#5	579	01 00 00 00 2a
		live	%42			#6	584	01 00 00 00 2a
		sti		r16,%402,r2	#6	590	0b 64 10 01 92 02
		sti		r16,%448,r2	#6	596	0b 64 10 01 c0 02
		zjmp	442			#3	602	09 01 ba
		live	%42			#5	605	01 00 00 00 2a
