#include "neural_network.h"

void update(float **w_input,     // hidden_neuron1 x input_neuron
            float **w_hidden,    // hidden_neuron2 x hidden_neuron1
            float **w_output,    // output_neuron x hidden_neuron2
            float *b_input,      // hidden_neuron1
            float *b_hidden,     // hidden_neuron2
            float *b_output,     // output_neuron
            float **dw_output,   // output_neuron x hidden_neuron2
            float *db_output,    // output_neuron
            float **dw_hidden,   // hidden_neuron2 x hidden_neuron1
            float *db_hidden,    // hidden_neuron2
            float **dw_input,    // hidden_neuron1 x input_neuron
            float *db_input,     // hidden_neuron1
            float **m_w_input,   // hidden_neuron1 x input_neuron
            float **v_w_input,   // hidden_neuron1 x input_neuron
            float **m_w_hidden,  // hidden_neuron2 x hidden_neuron1
            float **v_w_hidden,  // hidden_neuron2 x hidden_neuron1
            float **m_w_output,  // output_neuron x hidden_neuron2
            float **v_w_output,  // output_neuron x hidden_neuron2
            float *m_b_input,    // hidden_neuron1
            float *v_b_input,    // hidden_neuron1
            float *m_b_hidden,   // hidden_neuron2
            float *v_b_hidden,   // hidden_neuron2
            float *m_b_output,   // output_neuron
            float *v_b_output,   // output_neuron
            float learning_rate,
            float beta1,
            float beta2,
            float epsilon,
            int t)
{
    float beta1_t = pow(beta1, t);
    float beta2_t = pow(beta2, t);

    // Update the first hidden layer weight and bias
    for (int i = 0; i < hidden_neuron1; i++)
    {
        for (int j = 0; j < input_neuron; j++)
        {
            m_w_input[i][j] = beta1 * m_w_input[i][j] + (1 - beta1)
                * dw_input[i][j];
            v_w_input[i][j] = beta2 * v_w_input[i][j] + (1 - beta2)
                * dw_input[i][j] * dw_input[i][j];

            float m_hat = m_w_input[i][j] / (1 - beta1_t);
            float v_hat = v_w_input[i][j] / (1 - beta2_t);

            w_input[i][j] -= learning_rate * m_hat / (sqrt(v_hat) + epsilon);
        }

        m_b_input[i] = beta1 * m_b_input[i] + (1 - beta1) * db_input[i];
        v_b_input[i] = beta2 * v_b_input[i] + (1 - beta2) * db_input[i]
            * db_input[i];

        float m_hat = m_b_input[i] / (1 - beta1_t);
        float v_hat = v_b_input[i] / (1 - beta2_t);

        b_input[i] -= learning_rate * m_hat / (sqrt(v_hat) + epsilon);
    }

    // Update the second hidden layer weight and bias
    for (int i = 0; i < hidden_neuron2; i++)
    {
        for (int j = 0; j < hidden_neuron1; j++)
        {
            m_w_hidden[i][j] = beta1 * m_w_hidden[i][j] + (1 - beta1)
                * dw_hidden[i][j];
            v_w_hidden[i][j] = beta2 * v_w_hidden[i][j] + (1 - beta2)
                * dw_hidden[i][j] * dw_hidden[i][j];

            float m_hat = m_w_hidden[i][j] / (1 - beta1_t);
            float v_hat = v_w_hidden[i][j] / (1 - beta2_t);

            w_hidden[i][j] -= learning_rate * m_hat / (sqrt(v_hat) + epsilon);
        }

        m_b_hidden[i] = beta1 * m_b_hidden[i] + (1 - beta1) * db_hidden[i];
        v_b_hidden[i] = beta2 * v_b_hidden[i] + (1 - beta2) * db_hidden[i]
            * db_hidden[i];

        float m_hat = m_b_hidden[i] / (1 - beta1_t);
        float v_hat = v_b_hidden[i] / (1 - beta2_t);

        b_hidden[i] -= learning_rate * m_hat / (sqrt(v_hat) + epsilon);
    }

    // Update the output weight and bias
    for (int i = 0; i < output_neuron; i++)
    {
        for (int j = 0; j < hidden_neuron2; j++)
        {
            m_w_output[i][j] = beta1 * m_w_output[i][j] + (1 - beta1)
                * dw_output[i][j];
            v_w_output[i][j] = beta2 * v_w_output[i][j] + (1 - beta2)
                * dw_output[i][j] * dw_output[i][j];

            float m_hat = m_w_output[i][j] / (1 - beta1_t);
            float v_hat = v_w_output[i][j] / (1 - beta2_t);

            w_output[i][j] -= learning_rate * m_hat / (sqrt(v_hat) + epsilon);
        }

        m_b_output[i] = beta1 * m_b_output[i] + (1 - beta1) * db_output[i];
        v_b_output[i] = beta2 * v_b_output[i] + (1 - beta2) * db_output[i]
            * db_output[i];

        float m_hat = m_b_output[i] / (1 - beta1_t);
        float v_hat = v_b_output[i] / (1 - beta2_t);

        b_output[i] -= learning_rate * m_hat / (sqrt(v_hat) + epsilon);
    }
}