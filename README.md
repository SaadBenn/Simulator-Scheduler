# Compilation
Run the following command to compile the program
`make`

and then to run the program, just type the name + the scheduler to run

1. Pure RR; pass 1 as the command line argumnet
2. Priority RR; pass 2 as teh command line argument
3. Shortest Job first; pass 3 as the command line argument
4. STRJ; pass 4 as the command line argument

So for instance, to run pure RR: 

`./main 1` 

***
# Analysis

## The two scheduling algorithms are:
1. Pure RR
2. Priority RR

### Stats for the different priorities using Pure RR 
| Priority 0 	| Priority 1 	| Priority 2 	|
|------------	|------------	|------------	|
| 10289      	| 8264       	| 10941      	|
| 10097      	| 8234       	| 11038      	|
| 10211      	| 8339       	| 10745      	|
| 9994       	| 8236       	| 10764      	|
| 10120      	| 8247       	| 11053      	|
| 10783      	| 8732       	| 11417      	|
| 10155      	| 8228       	| 11095      	|
| 10120      	| 8247       	| 11053      	|
| 10032      	| 8281       	| 10943      	|
| 10097      	| 8234       	| 11038      	|

Average for P_0 = 10189
Standard Dev for P_0 = 224.49785943053

Average for P_1 = 8304.2
Standard Dev for P_1 = 153.92480126492

Average for P_2 = 11008.7
Standard Dev for P_2 = 188.00534862368


### Stats for the different types of jobs using Pure RR
| Type 0 	| Type 1 	| Type 2 	| Type 3 	|
|--------	|--------	|--------	|--------	|
| 1113   	| 2815   	| 18138  	| 16070  	|
| 967    	| 2684   	| 17642  	| 16732  	|
| 2354   	| 3805   	| 16734  	| 15144  	|
| 1255   	| 2994   	| 17374  	| 15934  	|
| 1009   	| 2701   	| 17637  	| 16749  	|
| 2289   	| 3542   	| 17628  	| 16723  	|
| 1123   	| 2676   	| 17642  	| 16732  	|
| 1009   	| 2701   	| 17637  	| 16749  	|
| 1184   	| 2787   	| 17892  	| 15994  	|
| 967    	| 2884   	| 17642  	| 16732  	|

Average for type_0 = 1327
Sample Standard Deviation for type_0 = 532.77741860722

Average for type_1 = 3958.9
Sample Standard Deviation for type_1 = 3136.2330004853

Average for type_2 = 17596.6
Sample Standard Deviation for type_2 = 362.77302362037

Average for type_3 = 16355.9
Sample Standard Deviation for type_3 = 550.51318482546


***
### Stats for the different priorities using Priority RR
| Priority 0 	| Priority 1 	| Priority 2 	|
|------------	|------------	|------------	|
| 3400       	| 11198      	| 20192      	|
| 3354       	| 11170      	| 20277      	|
| 3399       	| 11202      	| 20191      	|
| 3393       	| 11182      	| 20165      	|
| 3392       	| 11198      	| 20188      	|
| 3410       	| 11029      	| 20142      	|
| 3384       	| 11194      	| 20271      	|
| 3406       	| 11198      	| 20201      	|
| 3431       	| 11198      	| 20227      	|
| 3402       	| 11199      	| 20191      	|

Average for P_0 = 3397.1
Standard Dev for P_0 = 19.728434076508

Average for P_1 = 11176.8
Standard Dev for P_1 = 52.851574138231

Average for P_2 = 20204.5
Standard Dev for P_2 = 42.760963506451


### Stats for the different types of jobs using Priority RR
| Type 0 | Type 1 | Type 2 | Type 3 |
|--------|--------|--------|--------|
| 7946   | 9291   | 13240  | 15302  |
| 8017   | 9508   | 13546  | 14662  |
| 7942   | 9297   | 13238  | 15308  |
| 7969   | 9315   | 13276  | 15145  |
| 7930   | 9292   | 13240  | 15302  |
| 8130   | 9543   | 13085  | 14718  |
| 7975   | 9333   | 13376  | 15152  |
| 7966   | 9291   | 13240  | 15302  |
| 8042   | 9287   | 13239  | 15302  |
| 7946   | 9293   | 13238  | 15305  |

Average for type_0 = 7986.3
Sample Standard Deviation for type_0 = 61.385937586171

Average for type_1 = 9345
Sample Standard Deviation for type_1 = 96.511369508698

Average for type_2 = 13271.8
Sample Standard Deviation for type_2 = 118.95358571962

Average for type_3 = 15149.8
Sample Standard Deviation for type_3 = 250.82122894382


***
#Comparision of the two algorithms
We can see from our results that the two algorithms run differently from each other, just judging by the priority times. In Pure RR, the priorities don't matter as we can see that all the times for the different priorities are jumbled up. Priority 0 doesn't run faster than priority 1. 
In Priority RR, we can see that the highest priorities are excuted first and they take less time as compared to the lower priorities. Priority 0 takes on average 3397 units to complete compared to 11000 or 20000 units for priority 1 and priority 2, respectively.

The two algrothims are different in terms of when we commpare the times for their priorties but when it comes the types of different jobs then they comparision is minimal. Both schedulers take less time to execute the shortest types jobs compared to medium, long or io types of jobs. 

The two schedulers treat the queue differently. In Pure RR, the priority times are all mixed up which means that this algorithm follows first in first served conept. For Priority RR, the highest priority jobs are completed first which means that we have different queues depending on the priority and we process the queue with the highest priority jobs and then once we are done with that, we process the other queues. 