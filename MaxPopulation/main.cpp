//
//  main.cpp
//  MaxPopulation
//
//  Created by adeeb mohammed on 12/01/20.
//  Copyright © 2020 adeeb mohammed. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>

/*
    Program to find the maximum population in an year
    given pairs of birth and death of a number of person
    there are more years which is having highest birth rate
    how ever we have to return any of them
    just focus on birth years only
    as death only decreases
    core twist = > just findout the overlapping birth and death years
    time compelxity is o(n) + o(y) n -> number of persons , y no of years
    space complexity is o(1)
 */

class Person{
public:
    int birthYear;
    int deathYear;
    Person(int birthYear,int deathYear){
        this->birthYear = birthYear;
        this->deathYear = deathYear;
    }
};

int getMinBirthYear(std::vector<Person> personArray){
    int minBirthYear = INT_MAX;
    for(auto person : personArray){
        if(person.birthYear < minBirthYear){
            minBirthYear = person.birthYear;
        }
    }
    return minBirthYear;
}


int getMaxBirthYear(std::vector<Person> personArray){
    int maxBirthYear = 0;
    for(auto person : personArray){
        if(person.birthYear > maxBirthYear){
            maxBirthYear = person.birthYear;
        }
    }
    return maxBirthYear;
}

void addDelta(std::vector<int> &deltaYear,
            int index,
            int value){
     deltaYear.at(index) += value;
}

void findDelta(std::vector<int> &deltaYear ,
               std::vector<Person> personArray,
               int firstBirth,
               int lastBirth
               ){
    for(auto person : personArray){
        addDelta(deltaYear, person.birthYear - firstBirth, 1);
        if(person.deathYear + 1 <= lastBirth){
            addDelta(deltaYear, person.deathYear - firstBirth + 1, -1);
        }
    }
}


int maxPopulationIndex(std::vector<int> deltaYear){
    int maxPopIndex   = 0;
    int runningSum    = 0;
    int maxRunningSum = 0;
    int  i = 0;
    for(auto numberOfPeople : deltaYear){
        runningSum += numberOfPeople;
        if(runningSum > maxRunningSum){
            maxRunningSum = runningSum;
            maxPopIndex = i;
        }
        i++;
    }
    return maxPopIndex;
}

int findMaxPopulationYear(std::vector<Person> personArray){
    int maxPopYearIndex = 0;
    int firstBirth = getMinBirthYear(personArray);
    int lastBirth  = getMaxBirthYear(personArray);
    std::vector<int> deltaYear(lastBirth - firstBirth + 1);
    findDelta(deltaYear, personArray , firstBirth ,lastBirth);
    maxPopYearIndex = maxPopulationIndex(deltaYear);
    return maxPopYearIndex + firstBirth;
}

int main(int argc, const char * argv[]) {
    std::vector<Person> personArray = {{2000,2001},{2001,2002}};
    std::cout << "Max Population year :->" << findMaxPopulationYear(personArray);
    return 0;
}
