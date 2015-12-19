/* Recommended reading:
 * Extra, Extra - Read All About It: Nearly All Binary Searches and
 * Mergesorts are Broken (by Joshua Bloch)
 */

int
binsearch(int a[], int key, unsigned int low, unsigned int high){
	while(low <= high){
		int mid    = (low + high) >> 1;
		int midval = a[mid];

		if(key < midval)
			high = mid - 1;
		else if(key > midval)
			low = mid + 1;
		else
			return mid;
	}

	return -1; /* key not found */
}
