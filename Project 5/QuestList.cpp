//Daniel Andres Fernandez
//daniel.fernandez16@myhunter.cuny.edu
//October 29, 2023
//Project 5

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "QuestList.hpp"

QuestList::QuestList() : DoublyLinkedList<Quest*>() {}

QuestList::QuestList(const std::string& file)
{
    std::ifstream fin(file);    //file = "quests.csv"
    if(!fin.is_open())
    {
        std::cout << "File cannot be opened." << std::endl;
    }

    //Skips header line
    std::string SKIP;
    std::getline(fin, SKIP);

    //Declaring varaibles for subheadings
    std::string QuestTitle, Description, Dependencies, Subquests;
    bool Completion_Status;
    int Experience_Points;

    std::vector <Quest*> subVect;
    std::vector <Quest*> depVect;
    std::string empty = "";

    while(std::getline(fin, empty))
    {
        //Allwoing us to create a stream from the line
        std::istringstream temp(empty);

        //QuestTitle, Description
        getline(temp, QuestTitle, ',');
        getline(temp, Description, ',');

        //Completion_Status and Experience Points
        std::string convert;
        getline(temp, convert, ',');
            std::istringstream(convert) >> Completion_Status;
        getline(temp, convert, ',');
            std::istringstream(convert) >> Experience_Points;

        //Dependencies
        getline(temp, Dependencies, ',');
        std::vector <Quest*> depVect;
        std::string dep = ""; 
        std::istringstream dep_stream(Dependencies); 

        while(getline(dep_stream, dep, ';'))
        {
            if(dep != "NONE")
            {
                if(getPosOf(dep) != -1)
                {
                    Node<Quest*> *depNode = getPointerTo(getPosOf(dep));
                    depVect.push_back(depNode -> getItem());
                }
                else
                {
                    Quest* newQuest = new Quest;
                    newQuest -> title_ = dep;
                    newQuest -> description_ = "NOT DISCOVERED";
                    newQuest -> completed_ = false;
                    newQuest -> experience_points_ = 0;
                    newQuest -> dependencies_ = {};
                    newQuest -> subquests_ = {};
                    addQuest(newQuest);
                    depVect.push_back(newQuest);
                }
            }
        }

        //Subquests
        getline(temp, Subquests, ',');
        std::vector <Quest*> subVect;
        std::string sub = "";
        std::istringstream sub_stream(Subquests);

        while(getline(sub_stream, sub, ';'))
        {
            if(sub != "NONE")
            {
                if(getPosOf(sub) != -1)
                {
                    Node<Quest*> *subNode = getPointerTo(getPosOf(sub));
                    subVect.push_back(subNode -> getItem());
                    addQuest(subNode -> getItem());
                }
                else
                {
                    Quest* newQuest = new Quest;
                    newQuest -> title_ = sub;
                    newQuest -> description_ = "NOT DISCOVERED";
                    newQuest -> completed_ = false;
                    newQuest -> experience_points_ = 0;
                    newQuest -> dependencies_ = {};
                    newQuest -> subquests_ = {};
                    addQuest(newQuest);
                    subVect.push_back(newQuest);
                }
            }
        }
        addQuest(QuestTitle, Description, Completion_Status, Experience_Points, depVect, subVect);
    }
}

/**
    @param: A string reference to a quest title
    @return: The integer position of the given quest if it is in the QuestList, -1 if not found.
*/
int QuestList::getPosOf(const std::string& questTitle) const
{
    Node<Quest*> *node1 = first_;
    int position = 0;
    while(node1 != nullptr)         //As long as the node doesn't point to the nullptr...
    {
    //If the node accesses the title in the LinkedList (node), and is equal to the questTitle we pass in, then...
        if(node1 -> getItem() -> title_ == questTitle)  
        {
            return position;        //Returns the position (int value) of the quest in QuestList
        }
        else
        {
            position++;             //Moves position to the next node, and check the next value
            node1 = node1 -> getNext();
        }
    } 
    return -1;                      //Return 1 if not found
}

/**
    @param: A string reference to a quest title
    @return: True if the quest with the given title is already in the QuestList
*/
bool QuestList::contains(const std::string& questTitle) const
{
    return getPosOf(questTitle) != -1;
}

/**
    @pre: The given quest is not already in the QuestList
    @param:  A pointer to a Quest object
    @post:  Inserts the given quest pointer into the QuestList. Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
            If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
           
    @return: True if the quest was added or updated successfully, False otherwise
*/
bool QuestList::addQuest(Quest* add)
{
    if(contains(add -> title_))
    {
        if(getPointerTo(getPosOf(add -> title_)) -> getItem() -> description_ != "NOT DISCOVERED")
        {
            return false;
        }
        else
        {
            getPointerTo(getPosOf(add -> title_)) -> getItem() -> description_ = add -> description_;
            getPointerTo(getPosOf(add -> title_)) -> getItem() -> completed_ = add -> completed_;
            getPointerTo(getPosOf(add -> title_)) -> getItem() -> experience_points_ = add -> experience_points_;
            getPointerTo(getPosOf(add -> title_)) -> getItem() -> dependencies_ = add -> dependencies_;
            getPointerTo(getPosOf(add -> title_)) -> getItem() -> subquests_ = add -> subquests_;
        
            return true;
        }
    }
    else
    {
        if(insert(getLength(), add))
        {
            for(auto i: add -> dependencies_)
            {
                if(!contains(i -> title_))
                {
                    addQuest(i);
                }
            }
            for(auto j: add -> subquests_)
            {
                if(!contains(j -> title_))
                {
                    addQuest(j);
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}

/**
    @param:  A reference to string representing the quest title
    @param:  A reference to string representing the quest description
    @param:  A reference to boolean representing if the quest is completed
    @param:  An reference to int representing experience points the quest rewards upon completion 
    @param:  A reference to vector of Quest pointers representing the quest's dependencies
    @param:  A reference to vector of Quest pointers representing the quest's subquests
    @post:   Creates a new Quest object and inserts a pointer to it into the QuestList. 
             If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
             Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
             

    @return: True if the quest was added or updated successfully, False otherwise

*/
bool QuestList::addQuest(const std::string& questTitle, const std::string& questDescription, const bool& questCompletion, const int& questXP, const std::vector<Quest*>& questDep, const std::vector<Quest*>& questSub)
{
    Quest* quest = new Quest(questTitle, questDescription, questCompletion, questXP, questDep, questSub);
    return addQuest(quest);
}

/**
    @param:  A Quest pointer
    @return: A boolean indicating if all the given quest's dependencies are completed
*/
bool QuestList::dependenciesComplete(Quest* dependencies)
{
//Loops through the size of the dependencies vector, which is accessed by the dependencies parameter we passed through
    for(int i = 0; i < dependencies -> dependencies_.size(); i++)
    {
        if(!(dependencies -> dependencies_[i] -> completed_))
        {
            return false;           //Return false if dependencies aren't complete
        }
    }  
    return true;                    //Return true if the dependency is complete
}   

/**
    @param: A Quest pointer
    @return: A boolean if the given quest is available.
    Note: For a quest to be available, it must not be completed, and its dependencies must be complete.
*/
bool QuestList::questAvailable(Quest* available)
{
    if(!dependenciesComplete(available) || available -> completed_)
    {
        return false;   //Returns false if quest is not available OR already completed
    }
    return true;        //Otherwise returns true
}

/**
    @param: A Quest pointer
    @post: Prints the quest title and completion status
    The output should be of the form:
    [Quest Title]: [Complete / Not Complete]
    [Quest Description]\n\n
*/
void QuestList::printQuest(Quest* print)
{
    std::string empty = "";         //This empty string will represent if our string is either Complete or Not Complete
    if(print -> completed_ == true)
    {
        empty = "Complete";         //If the quest is complete, then the empty string holds a string of "Complete"
    }
    else
    {
        empty = "Not Complete";     //If the quest is not complete, then the empty string holds a string of "Not Complete"
    }
    std::cout << print -> title_ << ": " << empty << std::endl << print -> description_ << "\n\n";
}

//QuestQuery Helper function
void QuestList::QueryHelp(Quest* dependencies)
{
    //If the quest has no dependency, or is already complete then...
    if(dependencies -> dependencies_.empty() || dependenciesComplete(dependencies)) 
    {
        std::cout << "Ready: " << dependencies -> title_ << std::endl;      //Will print out saying that the dependency is ready
        return;
    } 
    //Reccursive

    //Loops through the dependencies vector which is accessed by the dependency parameter we passed through
    for(int i = 0; i < dependencies -> dependencies_.size(); i++)
    {
        Quest* quest = dependencies -> dependencies_[i];
        if(!quest -> completed_)
        {
            QueryHelp(quest);           //Calls in this function again if the quest isn't completed
        }
    }
    std::cout << "  " << dependencies -> title_ << std::endl;
}

/**
    @param: A string reference to a quest title
    @post:  Prints a list of quests that must to be completed before the given quest can be started (incomplete dependencies).
            If any of the quest's incomplete dependencies have an incomplete dependency, recursively print the quests that need to be done in order, indenting incomplete quests. 
            The indentation for incomplete quests is 2 spaces: "  "    
            The format of the list should be of the following forms for each different case:

            Query: [Quest Title]
            No such quest.
    
            Query: [Quest Title]
            Quest Complete
    
            Query: [Quest Title]
            Ready: [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
              [Quest Title]
            
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
              [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
              [Dependency2]
              [Quest Title]
              
     If the given quest title is not found in the list, print "No such quest."
*/
void QuestList::questQuery(const std::string& questTitle)
{
    std::cout << "Query: " << questTitle << "\n";           //Will print Query: <Quest #> for ALL quests within the csv file
    if(!contains(questTitle)) 
    {
        std::cout << "No such quest." << std::endl;         //Will print "no such quest", if this quest doesn't exist
        return;
    } 
    Quest* quest = getPointerTo(getPosOf(questTitle)) -> getItem();
    if(quest-> completed_)
    {
        std::cout << "Quest Complete." << std::endl;        //Will print "quest complete" if the quest is complete (duh :D)
        return;
    } 
    else 
    {
        QueryHelp(quest);  //Calls the helper function if none of these if conditions are satisfied
    }
}

/**
    @return: An integer sum of all the experience gained
    Note: This should only include experience from completed quests 
*/
int QuestList::calculateGainedExperience()
{
    Node<Quest*> *node = first_;
    int xp = 0;
    while(node != nullptr)          //As long as the node doesn't equal to a null value....
    {
        if(node -> getItem() -> completed_)
        {
            xp = xp + node -> getItem() -> experience_points_; //Xp value goes up as we look in the next position of the LinkedList
        }
        node = node -> getNext();
    }
    return xp;
}

/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that can be gained from completing the main quest AND all its subquests.
    Note: Also consider the potential experience if a subquest itself has subquests.
*/
int QuestList::calculateProjectedExperience(Quest* mainQuest)
{
    int xp = 0;
    xp = xp + mainQuest -> experience_points_;
    for(int i = 0; i < mainQuest -> subquests_.size(); i++)             //Loops through the subquest vector while accessing the subquest of the MainQuest we passed in via parameter
    {
        xp = xp + calculateProjectedExperience(mainQuest -> subquests_[i]);   //ProjectedXP value goes up as we look in the mainQuest and its subquests
    }
    return xp;
}

/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that has already been gained by completing the given quest's subquests.
    Note: Also consider the experience gained if a completed subquest itself has subquests.  
*/
int QuestList::calculatePathwayExperience(Quest* mainQuest)
{
    int pathwayXP = 0;
    if(mainQuest -> completed_)                 //If the mainQuest is completed, then the pathwayXP will go up via the xp points of the mainQuest
    {
        pathwayXP = pathwayXP + mainQuest -> experience_points_;
    }
    for(int i = 0; i< mainQuest -> subquests_.size(); i++)            //Loops through the subquest vector while accessing the subquest of the MainQuest we passed in via parameter
    {
        pathwayXP = pathwayXP + calculatePathwayExperience(mainQuest -> subquests_[i]);       //PathwayXP value goes up as we look in the mainQuest and its subquests
    }
    return pathwayXP;
}



/**
    @param: A string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every quest in the list.
           With filter "COMPLETE":   Only print out the completed quests in the list.
           With filter "INCOMPLETE": Only print out the incomplete quests in the list.
           With filter "AVAILABLE":  Only print out the available quests in the list.
           If an invalid filter is passed, print "Invalid Filter\n"
    Printing quests should be of the form:
    [Quest title]: [Complete / Not Complete]  
    [Quest description]\n
*/
void QuestList::questHistory(const std::string& filter)
{
    if(filter != "NONE" && filter != "COMPLETE" && filter != "INCOMPLETE" && filter != "AVAILABLE")
    {
        std::cout << "Invalid Filter\n";
    }
    else
    {
        Node<Quest*> *questNode = first_;
        while(questNode != nullptr)
        {
            if(filter == "NONE")
            {
                printQuest(questNode -> getItem());          //Will call the printquest function with NO filter in place. Basically printing eveything
            }
            else if(filter == "COMPLETE")
            {
                if(questNode -> getItem() -> completed_)          //Will call the printquest function with the filter of those quests that are COMPLETE
                {
                    printQuest(questNode -> getItem());
                }
            }
            else if(filter == "INCOMPLETE")
            {
                if(!(questNode -> getItem() -> completed_))     //Will call the printquest function with the filter of those quests that are not COMPLETE
                {
                    printQuest(questNode -> getItem());
                }
            }
            else if(filter == "AVAILABLE")
            {
                if(questAvailable(questNode -> getItem()))
                {
                    printQuest(questNode -> getItem());         //Will call the printquest function with the filter of those quests that are AVAILABLE to the player
                } 
            }
            questNode = questNode -> getNext();                 //Checks the next quest in the node to see if it satisfies any of these conditions
        }
    }
}

//Helper function
void QuestList::quest_detail_helper (Quest* quest, int spaces) 
{
    std::string beef = "";
    for (int i = 0; i < spaces; i++)            //This for loop will print out the indentation for the subquests (double space)
    {  
        beef+= " ";                           
    }
   
    for(int i = 0; i< quest -> subquests_.size(); i++)
    {
        quest_detail_helper(quest -> subquests_[i], spaces+2);              //Calls helper function
        if(quest -> subquests_[i] -> completed_)
        {
            std::cout << beef << quest -> subquests_[i] -> title_ << ": Complete\n";        //Will print if the subquest is complete
        }
        else
        {
            std::cout << beef << quest -> subquests_[i] -> title_ << ": Not Complete\n";   //Will print if the subquest is NOT complete
        }
    }
}

/**
    @param: A quest pointer to a main quest
    @post:  Outputs subquest pathway. Print quest names with two spaces ("  ") of indentation for each subquest, recursively.
            Also print the percentage of experience gained in this pathway, rounded down to the lower integer.
            The format should be of the form:
            [Main Quest] ([Pathway XP] / [Projected XP]% Complete)
                [Subquest0]: [Complete / Not Complete]
                    [Sub-Subquest01]: [Complete / Not Complete]
                        [Sub-Subquest011]: [Complete / Not Complete]
                    [Subquest02]: [Complete / Not Complete]
            Hint: You can write a helper function to print the subquests recursively. If the given quest is already marked as completed, you can assume that all of its subquests are also completed.
*/
void QuestList::printQuestDetails(Quest* mainQuest) 
{
    double pathXP = calculatePathwayExperience(mainQuest);              //Double variable for PathwayXP
    double projXP = calculateProjectedExperience(mainQuest);            //Double variable for ProjectedXP
    std::cout << mainQuest -> title_ << " (" << int((pathXP / projXP) * 100) << '%' << " Complete)" << std::endl;           //Prints out the percentage of said quest we are looking at
    if(mainQuest -> completed_)
    {
        return;
    }
    quest_detail_helper(mainQuest, 2);      //Calls helper function
}