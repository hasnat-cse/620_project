



i=1
while [ $i -le 9 ]
do


echo "solving TPP problem #$i"

./SatPlan2006_LinuxBin/satplan  -domain ../domains/TPP-Propositional-IPC5/domain.pddl  -problem ../domains/TPP-Propositional-IPC5/p0$i.pddl  -solution ./TPP_solutions/sol_0$i


i=`expr $i + 1`
done



i=10
while [ $i -le 30 ]
do



echo "solving TPP problem #$i"

./SatPlan2006_LinuxBin/satplan  -domain ../domains/TPP-Propositional-IPC5/domain.pddl  -problem ../domains/TPP-Propositional-IPC5/p$i.pddl  -solution ./TPP_solutions/sol_$i



i=`expr $i + 1`
done


