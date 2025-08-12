#include "sampler.h"

void sampler::sample_process(){
    int rd_val, wr_val, mcm;
    bool trig=trigger.read();
    if(trig){
        rd_val= (unsigned int) val.read();
        if(rd_val<min_val)
            min_val=rd_val;
        else if(rd_val>max_val)
            max_val=rd_val;
        mcm=min_max.read();
        wr_val = mcm > 0 ? max_val :
                (mcm < 0 ? min_val : rd_val);
        s_val.write(wr_val);
        if(!convert_bcd(wr_val))
            cout << "Range Error" << endl;
    }
}

bool sampler::convert_bcd(int a){
    if (a<0 || a>999) return(false);
    int b = a%10;
    s_val_1.write(b);
    s_val_10.write(((a-b)%100)/10);
    s_val_100.write(a/100);
    return(true);
}