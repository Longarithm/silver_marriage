double change(vector<int> s, int i1, int i2) {
    return 0;
}

void anneal(vector<int> s) {  
    const int COOLING_STEPS = 1E5;
    const int STEPS_PER_TEMP = 10;
    const int COOLING_FRACTION = 0.98;

    int i1, i2;  
    double temperature;
    double startVal, curVal;
    double delta, merit, flip, index;
        
    temperature = 1.0;                          
    
    curVal = 0; //initialize

    for (int i = 0; i < COOLING_STEPS; i++) {
        temperature *= COOLING_FRACTION;
        startVal = curVal; 

        for (int j = 0; j < STEPS_PER_TEMP; j++) {
            i1 = rand() % n;
            i2 = rand() % n;
            
            flip = (rand() % 1000000) * 1.0 / 999999.0;   
            delta = change(s, i1, i2);
            index = (-delta / curVal) / temperature;
            merit = 1.0 / (1.0 + exp(index));

            //minimize energy
            if (delta < 0) //good
                curVal += delta;
            else {
                if (merit > flip) //not so good
                    curVal += delta;
                else //bad
                    change(s, i2, i1); 
            }                                                

        }

        if (curVal - startVal < 0.0) //succeed
            temperature = temperature / COOLING_FRACTION;
    }
}