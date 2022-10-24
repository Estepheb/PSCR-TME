#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

void PoolWorker(Queue<Job>& queue)
{
	while(true)
	{
		//std::cout<<"run"<<std::endl;
		Job* j = queue.pop();
		if(j==nullptr)break;
		
		j->run();
		delete j;
	}
}


class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(size_t qsize):queue(qsize){}

	void start (int nbthread){
		for(int i=0;i<nbthread;i++)
			threads.emplace_back(PoolWorker,std::ref(queue));
	}
	void submit (Job * job) {queue.push(job);}
	void stop(){
		queue.SetBlocking();
		for(auto& t:threads){
			t.join();
		}
	}
	~Pool() {}
};

}
