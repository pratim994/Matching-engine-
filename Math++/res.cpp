//implementation of reservoir sampling algorithm

// choose k samples from a list of n items 
// typically n is large enough to not fit in main memory
// ex list of search qaueries of google and facebook
//
//
// Problem statement: for elements a1 , a2, a3 ..... an P(ai) = 1/n 

	p(ai) = P(ai getting chosen at ith step) * P(ai not getting replaced by ai+1, ai+2 , .... an)

	p(ai) = (1/i)*(1-1/i+1)*(1-1/i+2)*...(1-1/n)

	p(ai) = (1/i)*(i+1-1/i+1)*(i+2-1/i+2)*...(n-2/n-1)*(n-1/n)

	//so the equation simplifies to be 

	P(ai) = 1/n ∀ i


	template <typename T>

	class simpleWeightedReservoir {
	
	public:
		
		void Add(const T& sample, float weight){
			
			totalWeight += weight;

			float p = weight / toatlWeight;

			if((float)rand()/RAND_MAX < p) {
				
				choosen = sample;

				chosenWeight = weight;
			}

		}
		T Get() const {
			
			return chosen;
		}

	private:
		float totalWeight = 0;
		
		float chosenWeight = 0;

		T chosen;
	};





/*Leetcode problem #382 LinkedLIst Random node
  Given a singly linked List , implement the solution class and get random method */




class Solution {
	public :
		Solution(ListNode* head) : m_head(head) {

		}

		int getRandom() {
			int nodesSeenTillNow = {};
			
			ListNode *curr = m_head;
		
			ListNode *randomNOde = nullptr;

			while(curr != nullptr) {
				++nodesSeenTillNow;

				int randomIndex = rand()%nodesSeenTillNow;

				if(randomIndex == nodesSeenTillNow-1) randomNode = curr;

				curr = curr->next;
			}

			return randomNode->val;
		}

	private:
		ListNode *m_head = nullptr;
};




