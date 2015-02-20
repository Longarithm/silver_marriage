double change(vector<int> s, int i1, int i2) {
    return 0;
}

void anneal(vector<int> s) {  
    const int COOLING_STEPS = 1E5;
    const int STEPS_PER_TEMP = 10;
    const int COOLING_FRACTION = 0.98;

    int i1, i2;  
    double temperature;
    double startval, curval;
    double delta, merit, flip, index;
        
    temperature = 1.0;                          
    
    curval = 0; //initialize

    for (int i = 0; i < COOLING_STEPS; i++) {
        temperature *= COOLING_FRACTION;
        startval = curval; 

        for (int j = 0; j < STEPS_PER_TEMP; j++) {
            i1 = rand() % n;
            i2 = rand() % n;
            
            flip = (rand() % 1000000) * 1.0 / 999999.0;   
            delta = change(s, i1, i2);
            index = (-delta / curval) / temperature;
            merit = 1.0 / (1.0 + exp(index));

            //minimizate energy
            if (delta < 0) //good
                curval += delta;
            else {
                if (merit > flip) //not so good
                    curval += delta;
                else //bad
                    change(s, i1, i2); 
            }                                                

        }

        if (curval - startval < 0.0) //succeed
            temperature = temperature / COOLING_FRACTION;
    }
}