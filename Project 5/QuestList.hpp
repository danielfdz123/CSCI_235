//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//October 29, 2023
//Project 5

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "DoublyLinkedList.hpp"
#ifndef QUESTLIST_HPP
#define QUESTLIST_HPP

struct Quest
{
//Data Members
    std::string title_;
    std::string description_;
    bool completed_;
    int experience_points_;
    std::vector<Quest*> dependencies_;
    std::vector<Quest*> subquests_;

/**
        Default Constructor
        @post: Creates a new Quest object with default values (zero-initialized)
*/

    Quest() : title_{""}, description_{""}, completed_{0}, experience_points_{0}
    {
        dependencies_ = {};
        subquests_ = {};
    };

/*
    @param: A string reference to a quest title
    @param: A string reference to a quest description
    @param: A boolean representing if the quest is completed
    @param: A vector of Quest pointers representing the quest's dependencies
    @param: A vector of Quest pointers representing the quest's subquests
    @post: Creates a new Quest object with the given parameters
*/

    Quest(const std::string& title, const std::string& description, bool completion, int xp, const std::vector<Quest*>& dependencies, const std::vector<Quest*>& subquests): 
    title_{title}, description_{description}, completed_{completion}, experience_points_{xp}
    {
        for(int i = 0; i < dependencies.size(); i++)
        {
            dependencies_.push_back(dependencies[i]);
        }
        for(int i = 0; i < subquests.size(); i++)
        {
            subquests_.push_back(subquests[i]);
        }
    };
};

class QuestList : public DoublyLinkedList<Quest*>
{
    public:
    /**
    Default Constructor
    */
        QuestList();
    
    /**
    @param: a reference to string name of an input file
    @pre: Formatting of the csv file is as follows:
        Title: A string
        Description: A string
        Completion Status: 0 (False) or 1 (True)
        Experience Points: A non negative integer
        Dependencies: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
        Subquests: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The dependencies and subquests are separated by a semicolon and may be NONE.
        - The dependencies and subquests may be in any order.
        - If any of the dependencies or subquests are not in the list, they should be created as new quests with the following information:
            - Title: The title of the quest
            - Description: "NOT DISCOVERED"
            - Completion Status: False
            - Experience Points: 0
            - Dependencies: An empty vector
            - Subquests: An empty vector
        - However, if you eventually encounter a quest that matches one of the "NOT DISCOVERED" quests while parsing the file, you should update all the quest details.
        Hint: update as needed using addQuest()
        

    @post: Each line of the input file corresponds to a quest to be added to the list. No duplicates are allowed.

    */
        QuestList(const std::string& file);
    
    //Functions
        int getPosOf(const std::string& questTitle) const;
        bool contains(const std::string& questTitle) const;
        bool addQuest(Quest* add);
        bool addQuest(const std::string& questTitle, const std::string& questDescription, const bool& questCompletion, const int& questXP, const std::vector<Quest*>& questDep, const std::vector<Quest*>& questSub);
        bool dependenciesComplete(Quest* dependencies);
        bool questAvailable(Quest* available);    
        void printQuest(Quest* print);
        void questQuery(const std::string& questTitle);
        int calculateGainedExperience();
        int calculateProjectedExperience(Quest* mainQuest);
        int calculatePathwayExperience(Quest* mainQuest);
        void questHistory(const std::string& filter = "NONE");
        void printQuestDetails(Quest* mainQuest);

    //Helper Function
        void QueryHelp(Quest* dependencies);
        void quest_detail_helper(Quest *quest, int spaces);
};

#endif