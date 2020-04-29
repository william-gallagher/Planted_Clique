
success=0
trials=20
ret=0

counter=28
while [ $counter -lt 129 ];
do

    ./main $trials $counter
    printf "For k = %d we see %d success in %d trials\n"  $counter  $? $trials 

    counter=$((counter+1))
done


