#include <iostream>
#include <iomanip>
#include "fifo_2.h"

fifo_2::fifo_2(sc_module_name name, unsigned int fifo_size) : fifo_size(fifo_size) {
	// initialization of member variables/ports
	fifo_data = new unsigned char[fifo_size];
	wr_ptr = 0;
	rd_ptr = 0;
	fill_level = 0;
}

bool fifo_2::write_fifo(unsigned char *data, unsigned int &count) {
	bool result = false;

	unsigned int len; // amount of data written
	unsigned char *ptr; // pointer where to put data
	ptr = data;
	sc_time delay;

	if(fill_level + (int)count > fifo_size) // not enough space for all data
		len = fifo_size - fill_level; 		// none or less data will be written
	else {
		len = count;
		result = true;
	}

	unsigned int first_part;
	
	if(len > 0)
	{
		delay = sc_time(len+100, SC_NS);

		wait(delay);

		if(wr_ptr+len < fifo_size)  
			memcpy((fifo_data+wr_ptr), ptr, len);
		else{
			first_part = fifo_size-wr_ptr; 
			memcpy((fifo_data+wr_ptr), ptr, first_part);
			memcpy((fifo_data), ptr+first_part, len-first_part);
		}

		wr_ptr = (wr_ptr+len)%fifo_size;

		fill_level = fill_level + len;
	}
	else{
		//cout << endl << sc_time_stamp() << " " << name() <<": full - no data have been written"<<endl;
		}
	count=len;


	if(fifo_size <= 50)
		output_fifo_status();
	return result;
}

bool fifo_2::read_fifo(unsigned char *data, unsigned int &count) {
	bool result = false;

	unsigned int len;	// amount of data read
	unsigned char *ptr;	// pointer where to put data
	ptr = data;
	sc_time delay;

	if(fill_level < count)	// not enough data to read
		len = fill_level;	// none or less data will be read
	else {
		len = count;
		result = true;
	}


	unsigned int first_part;

	if(len > 0)
	{
		
		delay = sc_time(len*100, SC_NS);

		wait(delay);

		if(rd_ptr+len < fifo_size)  
			memcpy(ptr, (fifo_data+rd_ptr), len);
		else{
			first_part = fifo_size-rd_ptr; 
			memcpy(ptr, (fifo_data+rd_ptr), first_part);
			memcpy(ptr+first_part, (fifo_data), len-first_part);
		}

		rd_ptr = (rd_ptr+len)%fifo_size;
		fill_level = fill_level - len;

		//cout << endl <<std::setw(9) << sc_time_stamp() << ": '"<< name() <<"\t" << len << " words have been read:"<< ": 0x ";
		//cout << hex;
		//for(unsigned int i=0;i<len;i++)
			//cout << std::setw(2) << std::setfill('0') << (int)*(ptr+i) << " ";
		//cout << dec  << " read. " << endl;

	}
	else{
		//cout << endl << sc_time_stamp() << " "<< name()<< ": empty - no data have been read"<<endl;
		}
	count=len;

	if(fifo_size <= 50)
		output_fifo_status();
	return result;
}

// helper function to output content of FIFO
void fifo_2::output_fifo_status() {
	cout << "\tCurrent status of '" << name() << "': write address: "
			<< wr_ptr << ", read address: " << rd_ptr
			<< ", fill level: " << fill_level << endl;
	cout << "\t";
	cout << hex; // switch to hexadecimal mode;
	if(fill_level == 0) {
		for(unsigned int i = 0; i < fifo_size; i++)
			cout << "-- ";
	}
	else if(fill_level == fifo_size) {
		for(unsigned int i = 0; i < fifo_size; i++)
			cout << std::setw(2) << std::setfill('0') << (int)*(fifo_data + i)
					<< " ";
	}
	else if(wr_ptr > rd_ptr) {
		for(unsigned int i = 0; i < fifo_size; i++) {
			if((i >= rd_ptr) && (i < wr_ptr)) {
				cout << std::setw(2) << std::setfill('0')
						<< (int)*(fifo_data + i) << " ";
			}
			else
				cout << "-- ";
		}
	}
	else if(wr_ptr < rd_ptr) {
		for(unsigned int i = 0; i < fifo_size; i++) {
			if((i >= rd_ptr) || (i < wr_ptr)) {
				cout << std::setw(2) << std::setfill('0')
						<< (int)*(fifo_data + i) << " ";
			}
			else
				cout << "-- ";
		}
	}
	cout << dec << std::setfill(' ') << endl << endl;
}
