# Analysis

## The two scheduling algorithms chosen for analysis are:
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

```
Average for P_0 = 10189

Standard Dev for P_0 = 224.49785943053

Average for P_1 = 8304.2

Standard Dev for P_1 = 153.92480126492

Average for P_2 = 11008.7

Standard Dev for P_2 = 188.00534862368
```

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

```
Average for type_0 = 1327

Sample Standard Deviation for type_0 = 532.77741860722

Average for type_1 = 3958.9

Sample Standard Deviation for type_1 = 3136.2330004853

Average for type_2 = 17596.6

Sample Standard Deviation for type_2 = 362.77302362037

Average for type_3 = 16355.9

Sample Standard Deviation for type_3 = 550.51318482546

```

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

```
Average for P_0 = 3397.1

Standard Dev for P_0 = 19.728434076508

Average for P_1 = 11176.8

Standard Dev for P_1 = 52.851574138231

Average for P_2 = 20204.5

Standard Dev for P_2 = 42.760963506451

```

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

```
Average for type_0 = 7986.3

Sample Standard Deviation for type_0 = 61.385937586171

Average for type_1 = 9345

Sample Standard Deviation for type_1 = 96.511369508698

Average for type_2 = 13271.8

Sample Standard Deviation for type_2 = 118.95358571962

Average for type_3 = 15149.8

Sample Standard Deviation for type_3 = 250.82122894382
```

***
# Comparision of the two algorithms
We can see from our results that the two algorithms run differently from each other, just judging by the priority average times and  average times for the different types. In Pure RR, the priorities don't matter as we can see that all the times for the different priorities are jumbled up. Priority 0 doesn't run faster than priority 1. 
In Priority RR, we can see that the highest priorities are excuted first and they take less time as compared to the lower priorities. Priority 0 takes on average 3397 units to complete compared to 11000 or 20000 units for priority 1 and priority 2, respectively.

The two algrothims are different in terms of when we compare the times for their priorties but when it comes to the types of different jobs then the comparision is minimal. Both schedulers take less time to execute the shortest types jobs compared to medium, long or io types of jobs. Although, it should be noted that Pure RR does take less time executing the different types of jobs compared to Priority RR but the distribution is different when we reflect on the average times for the different priorities take to complete. 

The two schedulers treat the queue differently. In Pure RR, the priority times are all mixed up, so for instance, the averages are 10189, 8304.2, and 11008.7 for P_0, P_1 and P2 respectively which means that this algorithm follows first in first served conept as there is no logical order to the jobs in their averages. Similarly, the average for type 2 job is 17596.6 and type 3 job is 16355.9 which further enhances my argument that pure RR works on first come first served basis. So the queue will process the jobs in the order they are stored in the queue so whoever is first will get process time, a good analogy would be a line for a cashier in a bank.

For Priority RR, the highest priority jobs are completed first as can be seen from the average times for P_0, P_1 and P_2 which are 3397.1, 11176.8 and 20204.5 respectively. This means that we have different queues depending on the priority and we process the queue with the highest priority jobs first which is proved by the lowest time taken for piorities 0 jobs from our sample and then once we are done with that, we process the other queues in ascending order. The jobs are stored in the queue in terms of their priorities so the highest priority jobs are stored first in a queue and then the second highest priority are stored in a (probably) different queue and so on. The highest priority queue jobs get cpu time and once the jobs are done we move to the next highest priority queue. This cycle repeats untill all the priojobs are done.
