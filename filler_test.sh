#!/bin/bash


p1="ksuomala.filler"
p2=""
vm_path="resources/filler_vm_old"
log_dir="test_logs"
log_file="$log_dir/test_log"
map_dir="resources/maps"
players_dir="resources/players"
games_lost=0
os=$(uname -s | tr A-Z a-z)

rm -rf $log_dir
mkdir $log_dir
touch $log_file

echo YOUR OS is $os
read -n 1 -p "Do you want to manually select a player? [y / n] If n is selected, all the players in $players_dir will be played against." select_player
echo
if [ $select_player == "y" ]
then
	ls $players_dir
	read -p "Type name for PLAYER2 and press ENTER " p2
	echo "$p2 set as PLAYER2"
fi
read -n 1 -p "Do you want to visualize the games that you lose? [y/n]" visualize
echo
read -n 1 -p "Do you want to quit if you lose a single game? [y/n] " quit_if_lose
echo

loop_games()
{
		# checking wether to display colors or not
		for map in $map_dir/*
		do
			if [ $os = "linux" ]
			then
				echo -e "Running map \e[33m$map\e[0m 5 times. \e[32m$1\e[0m as player1"
			else
				echo "Running map $map 5 times. $1 as player1"
			fi
			games_won=0
			for i in {1..5}
			do
				./$vm_path -f $map -p1 ./$1 -p2 ./$2 > $log_file
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
				if [[ "$winner" == *"$p1"* ]];
				then
					echo -n 1
					games_won=$(($games_won+1))
				elif [[ "$winner" == *"$p2"* ]];
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
			if [ $games_won -lt $(($i/2)) ]
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
		done
}


if [ $select_player != "y" ]
then
	for player in $players_dir/*
	do
		p2=$player
		if [ $os = "linux" ]
		then
			echo -e "\e[34m$p1 \e[0mvs \e[35m$p2\e[0m"
		else
			echo "$p1 vs $p2"
		fi
		loop_games $p1 $p2
		loop_games $p2 $p1
	done
else
	if [ $os = "linux" ]
	then
		echo -e "\e[34m$p1 \e[0mvs \e[35m$p2\e[0m"
	else
		echo "$p1 vs $p2"
	fi
	loop_games $p1 $p2
	loop_games $p2 $p2
fi
