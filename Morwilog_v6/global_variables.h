#include <cmath>

//Definition of data types for each of the fields
//A: long
//B: IP address
//C: Nominal values (finite set of options)

#define LONG_VALUE 'A'
#define IP_ADD_VALUE 'B'
#define NOMINAL_VALUE 'C'

//It indicates the proportion of logs that has to be erased in the creation of the trees, for each field selected (IP source by default)
const double PROPORTION_ERASE = 0.20;

const int TREES_DEPTH = 5;
const long MAX_TIME_SEARCH = 62;//60

//ABOUT POSITIONS IN FIELDS
const int FIELD_TO_CLASSIFY = 3; //We classify by IP source
const int POSITION_TIMESTAMP = 1;

//LATER WE HAVE TO ADAPT IT IN A CONFIG FILE
//REVIEW
const long INITIAL_PH = 1000;
const long INCREMENT_PH = 110;
const long DECREMENT_PH = -110;
const double EVAPORATION_RATE = 0.02;
const long MINIMUM_PH_ATTACK = 200;
const long MINIMUM_PH = 100;//It has to be < minimum_ph_attack (even minimum_ph_attack-1 is valid)

//IF we introduce Gaussian evaporation and modification of pheromones
const double GAUSS_A_DELTA = 500;
//const double GAUSS_A_EVAP = 100;
const double GAUSS_B = INITIAL_PH;
const double GAUSS_C = 1000; //1000
const double GAUSS_DENOM = 2*pow(GAUSS_C,2);

//It states in how many parts we have to divide the set of log for taking one part as training data and the rest as testing data
#define PARTS_OF_SET 1

//Number of logs on each part of training/test
//#define SUBSET_SIZE 500

//FOR MODIFYING THE PARAMETERS OF THE LOG GENERATION ON-THE-FLY
//1) num_log
//2) num_typ_attack
//3) num_typ_inn
//4) prop_attack
//5) prop_inn
//6) ....
const int POS_NUM_LOG = 1;
const int POS_NUM_TYP_ATTACK = 2;
const int POS_NUM_TYP_INN = 3;
const int POS_PROP_ATTACK = 4;
const int POS_PROP_INN = 5;
const int POS_MAX_SIZE = 6;
const int POS_MAX_STEP = 7;
const int POS_PROB_EXISTENT_SRC = 8;

//
const double PROB_CREATE_TREE = 0.5;
const double PROB_RANDOM_JUMP = 0.1;
//const int MAX_RANDOM_JUMP = 50; //200
const long MINIMUM_PH_ERASE = MINIMUM_PH;
const int MAX_RANDOM_POSITION_SHIFT = 3; //Indicates which is the maximum jump we can make.
const int CHILDREN_AT_EACH_LEVEL = 1;
const long PH_JUMP_CHILDREN = MINIMUM_PH_ATTACK;
const long PH_JUMP_NO_CHILDREN = MINIMUM_PH_ATTACK;

//For indicating if we want to simulate without the pheromone update (like random search)
const bool NO_PHEROMONES = false;
