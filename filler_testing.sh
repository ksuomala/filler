#!/bin/bash

player1="ksuomala.filler"
map_dir="resources/maps/"
vm_path="resources/filler_vm_old"
log_dir="test_logs"
log_file="$log_dir/script_log"
map_dir="resources/maps/*"
players_dir="resources/players"
games_lost=0
os=$(uname -s | tr A-Z a-z)

rm -f $log_file $log_dir/error
rm -rf $log_dir
touch $log_file
mkdir $log_dir

echo $player1 is player 1!
echo "Players in $players_dir:"
ls $players_dir
read -p "Type player2 name and press ENTER " player2
echo $player2 is player 2!
read -n 1 -p "Do you want to visualize the games that you lose? [y/n]" visualize
echo
read -n 1 -p "Do you want to quit if you lose a single game? [y/n] " quit_if_lose
echo
echo YOUR OS is $os
for map in $map_dir
do
	if [ $os = "linux" ]
	then
		echo -e "Running map \e[34m$map\e[0m 10 times as p1 and p2..."
	else
		echo "Running map $map 10 times as both players..."
	fi
	echo p1
	games_won=0
	for i in {1..10}
	do
		./$vm_path -f $map -p1 ./$player1 -p2 ./$players_dir/$player2 > $log_file
		grep -A1 "error" $log_file > $log_dir/error

		if [ -s $log_dir/error ]
		then
			cat $log_dir/error
			exit
		fi
		grep "Segfault" $log_file > $log_dir/error

		if [ -s $log_file/error ]
		then
			if [ $os = "linux" ]
			then
				echo -e "\e[31mSEGFAULT:\e[0m"
			else
				echo "SEGFAULT:"
			fi
			cat $log_dir/error
			exit
		fi
		winner=$(grep "won" filler.trace)
		if [[ "$winner" == *"$player1"* ]];
		then
			echo -n 1
			games_won=$(($games_won+1))
		fi
		if [[ "$winner" == *"$player2"* ]];
		then
			echo -n 2
			games_lost=$(($games_lost+1))
			cp $log_file $log_file$games_lost
			if [ $visualize = "y" ]
			then
				echo
				echo "visualizing..."
				./visualizer < $log_file
			fi
			if [ $quit_if_lose = "y" ]
			then
				echo
				echo You lost, quitting...
				exit
			fi
		fi
	done

	if [ $games_won -lt 5 ]
	then
		if [ $os = "linux" ]
		then
			echo -e "\e[31m $games_won/$i\e[0m"
		else
			echo " $games_won/$i"
		fi
	elif [ $os = "linux" ]
	then
		echo -e "\e[32m $games_won/$i\e[0m"
	else
		echo " $games_won/$i"
	fi

	echo p2
	games_won=0

	for i in {1..10}
	do
		./$vm_path -f $map -p1 ./$players_dir/$player2 -p2 ./$player1 > $log_file
		grep -A1 "error" $log_file > $log_dir/error

		if [ -s $log_dir/error ]
		then
			cat $log_dir/error
			exit
		fi
		grep "Segfault" $log_file > $log_dir/error
		if [ -s $log_dir/error ]
		then
			cat $log_dir/error
			exit
		fi
		winner=$(grep "won" filler.trace)
		if [[ "$winner" == *"$player1"* ]];
		then
			echo -n 1
			games_won=$(($games_won+1))
		fi
		if [[ "$winner" == *"$player2"* ]];
		then
			echo -n 2
			games_lost=$(($games_lost+1))
			cp $log_file $log_file$games_lost
			if [ $visualize = "y" ]
			then
				echo
				echo "visualizing..."
				./visualizer < $log_file
			fi
			if [ $quit_if_lose = "y" ]
			then
				echo
				echo "You lost. Quitting..."
				exit
			fi
		fi
	done
	if [ $games_won -lt 5 ]
	then
		if [ $os = "linux" ]
		then
			echo -e "\e[31m $games_won/$i\e[0m"
		else
			echo " $games_won/$i"
		fi
	elif [ $os = "linux" ]
	then
		echo -e "\e[32m $games_won/$i\e[0m"
	else
		echo " $games_won/$i"
	fi
	echo ""
done
