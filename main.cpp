#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

int main (int argc, char *argv[])
{
    srand(time(NULL));
    int n = 10 , i , j , k , sum , errorPercentage = 0 , ctr_unchg = 0 , ctr = 0;
    int m = static_cast<int>(0.138f*n);
    int* pattern = new int[m*n];
    int* w = new int[n*n];
    int* neuron = new int[n];
    int* neuron_prev = new int[n];

    cout<<"Hopfield Artificial Neural Network (A NN) :\n\n"<<"Training patterns :  ";

    /* Generate random pattern */
    for(j = 0 ; j < m ; j++)      /*rows*/
    {
        for(i = 0 ; i < n ; i++) /*columns*/
        {
            pattern[j*n+i] = rand()%2;
            cout << pattern[j*n+i];
        }
        cout << endl;
    }
    cout << endl;

    /*Find the Weight Matrix */
    for( j = 0 ; j < n ; j++)
        for( i = j ; i < n ; i++)
            if( i == j )
                w[j*n+i] = 0 ;
            else
              {
                sum = 0;
                for(k = 0 ; k < m ;k++)
                    sum+=(pattern[k*n+i]*2-1)*(pattern[k*n+j]*2-1); /* to convert bipolar to binary use f(x) = 2x -1 */
                w[j*n+i] = sum;
                w[i*n+j] = sum;
              }

    /* print the weight matrix */
    cout<<"The weight matrix :"<<endl<<endl;
    for(j=0;j<n;j++)
    {
        for(i=0;i<n;i++)
            printf("%2d ",w[j*n+i]);
        cout << endl;
    }
    cout << endl;

    /* Select one of the training patterns randomly*/
    cout<<"Pattern-recognition Test:"<<endl<<endl;
    int selectedPattern = rand()% 2;
    cout<<"Test pattern selected :  ";
    for(i = 0 ; i < n ; i++)
        cout << pattern[selectedPattern*n+i];

    cout << endl << endl;

    /* Save patterns */
    for(i = 0 ; i < n ; i++)
    {
        neuron[i] = pattern[selectedPattern*n+i];
        if(rand()%100 < errorPercentage ) neuron[i] = 1-neuron[i];
        neuron_prev[i] = neuron[i];
    }

    /* Pattern recognition */
    while(ctr_unchg < 100 && ctr < 1000)
    {
        for(k = 0 ; k < n ; k++)
        {
            j = rand()%n;
            sum = 0;
            for(i = 0 ; i < n ;i++)
                if(i != j)
                    sum+=neuron[i]*w[j*n+i];
            if(sum >= 0)
                neuron[j] = 1;
            else
                neuron[j] = 0;
        }

        bool changed = false;
        for(k = 0; k < n ; k++)
            if( neuron[k]!= neuron_prev[k])
            {
                changed = true;
                break;
            }
        if(changed == false)
            ctr_unchg++;
        else
            ctr_unchg=0;

        /* update the previous network state */
        for(k = 0 ; k < n; k++)
            neuron_prev[k] = neuron[k];

        ctr++;
    }


    if(ctr_unchg >= 100)
      {
        cout<<"Converged network state :  ";
        for(i = 0 ; i < n ; i++)
            cout<<neuron[i];
        cout<<endl<<endl;

        /* calculate the convergence error percentage */
        int sumDif=0; // total number of differences
        for(i = 0 ; i < n ; i++)
            if(neuron[i]!= pattern[selectedPattern*n+i])
                sumDif++;
        cout<< "Convergence error percentage : " << 100*sumDif / n <<endl;
    }
    else
        cout<<"The network did not reach the convergence limit set!"<<endl;

    /* Garbage collection */
    delete []pattern;
    delete []w;
    delete []neuron;
    delete []neuron_prev;

    return 0;
}
