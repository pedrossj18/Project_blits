#include "main.h"
#include "LiquidCrystal.h"

// Definições de constantes
#define menu_max 5  // Número máximo de opções no menu
#define min_value 1900  // Valor mínimo
#define max_value 2099  // Valor máximo
#define initial_value 2010  // Valor inicial ao entrar no menu

// Função de protótipos
void apresentacao();
void keyboard();
void menu1();
void menu2();
void menu3();
void menu4();
void menuValores();

// Variáveis globais
int menu_num = 1;
int sub_menu = 1;
int current_value = initial_value;  // Valor inicial para o menu de valores

uint8_t button_dir = 0;
uint8_t button_esq = 0;
uint8_t button_cima = 0;
uint8_t button_baixo = 0;

// Inicialização do LCD
LiquidCrystal lcd;

// Função de inicialização
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    // Inicializa o LCD
    begin(&lcd, 16, 2, LCD_5x8DOTS);

    apresentacao();

    // Loop principal
    while (1)
    {
        // Leituras dos Botões
        button_dir = HAL_GPIO_ReadPin(BT_DIR_GPIO_Port, BT_DIR_Pin);   // Botão direito
        button_esq = HAL_GPIO_ReadPin(BT_ESQ_GPIO_Port, BT_ESQ_Pin);   // Botão esquerdo
        button_cima = HAL_GPIO_ReadPin(BT_CIMA_GPIO_Port, BT_CIMA_Pin); // Botão cima
        button_baixo = HAL_GPIO_ReadPin(BT_BAIXO_GPIO_Port, BT_BAIXO_Pin); // Botão baixo

        // Verifica se exatamente um botão está pressionado.
        // A condição checa se apenas um dos quatro botões (direita, esquerda, cima ou baixo) está pressionado,
        // enquanto os outros três botões não estão pressionados.
        if ((button_dir == GPIO_PIN_SET && button_esq != GPIO_PIN_SET && button_cima != GPIO_PIN_SET && button_baixo != GPIO_PIN_SET) ||
            (button_esq == GPIO_PIN_SET && button_dir != GPIO_PIN_SET && button_cima != GPIO_PIN_SET && button_baixo != GPIO_PIN_SET) ||
            (button_cima == GPIO_PIN_SET && button_esq != GPIO_PIN_SET && button_dir != GPIO_PIN_SET && button_baixo != GPIO_PIN_SET) ||
            (button_baixo == GPIO_PIN_SET && button_esq != GPIO_PIN_SET && button_dir != GPIO_PIN_SET && button_cima != GPIO_PIN_SET))
        {
            // Acende o LED vermelho se apenas um dos botões estiver pressionado
            HAL_GPIO_WritePin(LED_VERMELHO_GPIO_Port, LED_VERMELHO_Pin, GPIO_PIN_SET);  // Acende o LED
        }
        else
        {
            // Apaga o LED vermelho se nenhum ou mais de um botão estiver pressionado
            HAL_GPIO_WritePin(LED_VERMELHO_GPIO_Port, LED_VERMELHO_Pin, GPIO_PIN_RESET);  // Apaga o LED
        }
        keyboard();  // Leitura dos botões

        // Controle do menu
        switch (menu_num)
        {
            case 1: menu1(); break;
            case 2: menu2(); break;
            case 3: menu3(); break;
            case 4: menu4(); break;
            case 5: menuValores(); break;// Menu para os valores de 1980 a 2060
        }
    }
}
// Fim da função "main"
// Função de leitura dos botões e navegação

// Função para exibir a apresentação ao ligar
void apresentacao()
{
    clear(&lcd);
    setCursor(&lcd, 0, 0);
    print(&lcd, (int8_t *)"   BEM-VINDO   ");
    setCursor(&lcd, 0, 1);
    print(&lcd, (int8_t *)"    INDFLOW    ");

    HAL_Delay(4000);  // Delay de 5 segundos

    clear(&lcd);  // Limpa a tela após o delay
}

//Configuração dos Botões
void keyboard()
{
    // Botão para aumentar a opção do menu
    if (HAL_GPIO_ReadPin(BT_CIMA_GPIO_Port, BT_CIMA_Pin) == GPIO_PIN_SET && sub_menu == 1)
    {
        HAL_Delay(150);
        if (menu_num < menu_max) menu_num += 1;  // Avança para o próximo menu
    }

    // Botão para diminuir a opção do menu
    if (HAL_GPIO_ReadPin(BT_BAIXO_GPIO_Port, BT_BAIXO_Pin) == GPIO_PIN_SET && sub_menu == 1)
    {
        HAL_Delay(150);
        if (menu_num > 1) menu_num -= 1;  // Volta para o menu anterior
    }

    // Botão para entrar na opção selecionada
    if (HAL_GPIO_ReadPin(BT_DIR_GPIO_Port, BT_DIR_Pin) == GPIO_PIN_SET)
    {
        HAL_Delay(150);
        if (sub_menu < 2) sub_menu += 1;  // Entra no submenu
    }

    // Botão para voltar ao menu anterior
    if (HAL_GPIO_ReadPin(BT_ESQ_GPIO_Port, BT_ESQ_Pin) == GPIO_PIN_SET)
    {
        HAL_Delay(150);
        if (sub_menu > 1) sub_menu -= 1;  // Volta ao menu principal
    }
}

// Funções dos menus
void menuValores()
{
    // Submenu para modificar o valor
    switch (sub_menu)
    {
        case 1:
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)"<PARAMETRIZACAO>");
            setCursor(&lcd, 0, 1);
            char buffer[16];
            snprintf(buffer, sizeof(buffer), "ENTRAR:    %d", current_value);
            print(&lcd, (int8_t *)buffer);
            break;

        case 2:
            // Navegação pelos valores entre 1980 e 2060
            if (button_cima == GPIO_PIN_SET)
            {
                HAL_Delay(20);
                if (current_value < max_value) current_value += 1;  // Aumenta o valor
            }
            if (button_baixo == GPIO_PIN_SET)
            {
                HAL_Delay(20);
                if (current_value > min_value) current_value -= 1;  // Diminui o valor
            }

            // Atualiza o display com o valor atual
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)" PARAMETRIZACAO ");
            setCursor(&lcd, 0, 1);
            snprintf(buffer, sizeof(buffer), "SENHA:     %d", current_value);
            print(&lcd, (int8_t *)buffer);
            break;
    }
}

void menu1()
{
    switch (sub_menu)
    {
        case 1:
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)"   Voltimetro  >");
            setCursor(&lcd, 0, 1);
            print(&lcd, (int8_t *)"                ");
            break;
        case 2:
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)"   Voltimetro   ");
            setCursor(&lcd, 0, 1);
            print(&lcd, (int8_t *)"   10.0 Volts   ");
            break;
    }
}

void menu2()
{
    switch (sub_menu)
    {
        case 1:
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)"<  Amperimetro >");
            setCursor(&lcd, 0, 1);
            print(&lcd, (int8_t *)"                ");
            break;
        case 2:
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)"   Amperimetro  ");
            setCursor(&lcd, 0, 1);
            print(&lcd, (int8_t *)"    1.5 Amps    ");
            break;
    }
}

void menu3()
{
    switch (sub_menu)
    {
        case 1:
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)"<  Ohmimetro   >");
            setCursor(&lcd, 0, 1);
            print(&lcd, (int8_t *)"                ");
            break;
        case 2:
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)"   Ohmimetro    ");
            setCursor(&lcd, 0, 1);
            print(&lcd, (int8_t *)"    100 Ohms    ");
            break;
    }
}

void menu4()

{
    switch (sub_menu)
    {
        case 1:
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)"<  Wattimetro  >");
            setCursor(&lcd, 0, 1);
            print(&lcd, (int8_t *)"                ");
            break;
        case 2:
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)"   Wattimetro   ");
            setCursor(&lcd, 0, 1);
            print(&lcd, (int8_t *)"    55 Watts    ");
            break;
    }
}


//Configuração do relógio do sistema
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
Função de inicialização GPIO
*/
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_VERMELHO_GPIO_Port, LED_VERMELHO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin|LCD_E_Pin|LCD_D5_Pin|LCD_D6_Pin
                          |LCD_D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_VERMELHO_Pin */
  GPIO_InitStruct.Pin = LED_VERMELHO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_VERMELHO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BT_DIR_Pin BT_CIMA_Pin BT_BAIXO_Pin BT_ESQ_Pin */
  GPIO_InitStruct.Pin = BT_DIR_Pin|BT_CIMA_Pin|BT_BAIXO_Pin|BT_ESQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RS_Pin LCD_E_Pin LCD_D5_Pin LCD_D6_Pin
                           LCD_D7_Pin */
  GPIO_InitStruct.Pin = LCD_RS_Pin|LCD_E_Pin|LCD_D5_Pin|LCD_D6_Pin
                          |LCD_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_D4_Pin */
  GPIO_InitStruct.Pin = LCD_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_D4_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief Informa o nome do arquivo fonte e o número da linha fonte
  * onde ocorreu o erro assert_param.
  * @param file: ponteiro para o nome do arquivo fonte
  * @param linha: número da fonte da linha de erro assert_param
  * @retval Nenhum
  */rt_failed(uint8_t *file, uint32_t line)
{
/* CÓDIGO DE USUÁRIO COMEÇO 6 */
/* O usuário pode adicionar sua própria implementação para relatar o nome do arquivo e o número da linha,
ex: printf("Valor de parâmetros errado: arquivo %s na linha %d\r\n", arquivo, linha) */
/* CÓDIGO DE USUÁRIO FIM 6 */
}
#endif /* USE_FULL_ASSERT */
