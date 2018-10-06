#include<iostream>
#include<thread>
#include<vector>
#include<chrono>
#include<numeric>

int main() {
		auto NUM_THREADS = std::thread::hardware_concurrency();
		std::cout << "Num Threads: " << NUM_THREADS << std::endl;

		auto start = std::chrono::high_resolution_clock::now();
		auto end = std::chrono::high_resolution_clock::now();

		std::vector<int> nums(100000, 2);

		start = std::chrono::high_resolution_clock::now();
		auto sum_1 = std::accumulate(nums.begin(), nums.end(), 0);
		end = std::chrono::high_resolution_clock::now();
		
		std::cout << "Elapsed Time (nanoseconds): " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << std::endl;
		std::cout << "Elapsed Time (micrseconds): " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << std::endl;

		start = std::chrono::high_resolution_clock::now();
		auto accum_func = [](int * first, int * second, int &result) {
				result = std::accumulate(first, second, 0);
				return;
		};

		int res1, res2;
		std::thread thread1(accum_func, &nums[0], &nums[nums.size()/2], std::ref(res1));
		std::thread thread2(accum_func, &nums[nums.size()/2], &nums[nums.size()], std::ref(res2));
		thread1.join();
		thread2.join();
		auto sum_2 = res1 + res2;
		end = std::chrono::high_resolution_clock::now();

		std::cout << "Elapsed Time (nanoseconds): " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << std::endl;
		std::cout << "Elapsed Time (micrseconds): " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << std::endl;
		std::cout << "Standard accumulate: " << sum_1 << std::endl;
		std::cout << "Conncurr accumulate: " << sum_2 << std::endl;
		return 0;
}
