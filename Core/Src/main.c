#include "main.h"
#include "LiquidCrystal.h"

// Definições de constantes
#define menu_max 5  // Número máximo de opções no menu
#define min_value 1980  // Valor mínimo
#define max_value 2060  // Valor máximo
#define initial_value 2010  // Valor inicial ao entrar no menu

// Função de protótipos
void apresentacao();
void keyboard();
void menu1();
void menu2();
void menu3();
void contato();
void parametrizacao();

// Variáveis globais
int menu_num = 1;  // Opção atual do menu
int sub_menu = 1;  // Indica se está no menu principal ou em um submenu
int current_value = initial_value;  // Valor inicial para o menu de valores

uint8_t button_confirm = 0;
uint8_t button_right = 0;
uint8_t button_up = 0;
uint8_t button_down = 0;

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
        button_confirm = HAL_GPIO_ReadPin(BT_ESQ_GPIO_Port, BT_ESQ_Pin);   // Botão de confirmação (esquerda)
        button_right = HAL_GPIO_ReadPin(BT_DIR_GPIO_Port, BT_DIR_Pin);   // Botão de navegação (direita)
        button_up = HAL_GPIO_ReadPin(BT_CIMA_GPIO_Port, BT_CIMA_Pin);   // Botão para aumentar
        button_down = HAL_GPIO_ReadPin(BT_BAIXO_GPIO_Port, BT_BAIXO_Pin);   // Botão para diminuir

        // Controle do menu e navegação
        keyboard();  // Leitura dos botões e navegação

        // Controle do menu atual
        switch (menu_num)
        {
            case 1: menu1(); break;
            case 2: menu2(); break;
            case 3: menu3(); break;
            case 4: contato(); break;
            case 5: parametrizacao(); break; // Menu para os valores de 1980 a 2060
        }
    }
}

// Função para exibir a apresentação ao ligar
void apresentacao()
{
    clear(&lcd);
    setCursor(&lcd, 0, 0);
    print(&lcd, (int8_t *)"   BEM-VINDO   ");
    setCursor(&lcd, 0, 1);
    print(&lcd, (int8_t *)"    INDFLOW    ");

    HAL_Delay(5000);  // Delay de 5 segundos

    clear(&lcd);  // Limpa a tela após o delay
}

// Função de navegação do menu com os botões
void keyboard()
{
    // Navegação entre as opções de menu com o botão direito
    if (button_right == GPIO_PIN_SET && sub_menu == 1)  // Quando estiver no menu principal
    {
        HAL_Delay(50);  // Debounce
        if (menu_num < menu_max)
            menu_num += 1;  // Avança para a próxima opção
        else
            menu_num = 1;   // Volta para a primeira opção se estiver na última
    }

    // Confirmação com o botão esquerdo (entrar ou sair do submenu)
    if (button_confirm == GPIO_PIN_SET)
    {
        HAL_Delay(50);  // Debounce
        if (sub_menu == 1)  // Se estiver no menu principal, entra no submenu
        {
            sub_menu = 2;  // Entra no submenu
        }
        else if (sub_menu == 2)  // Se estiver no submenu, volta para o menu principal
        {
            sub_menu = 1;  // Volta para o menu principal
        }
    }

    // Navegação nos valores com os botões cima e baixo no submenu
    if (sub_menu == 2 && menu_num == 5)  // Se estiver no submenu de valores
    {
        // Aumenta o valor com o botão de cima
        if (button_up == GPIO_PIN_SET)
        {
            HAL_Delay(50);
            if (current_value < max_value) current_value += 1;
        }

        // Diminui o valor com o botão de baixo
        if (button_down == GPIO_PIN_SET)
        {
            HAL_Delay(50);
            if (current_value > min_value) current_value -= 1;
        }
    }
}

// Funções dos menus
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

void contato()
{
    switch (sub_menu)
    {
    	case 1:
			setCursor(&lcd, 0, 0);
			print(&lcd, (int8_t *)" INF DE CONTATO ");
			setCursor(&lcd, 0, 1);
			print(&lcd, (int8_t *)"+55 11 5522-4655 ");
    }
}

void parametrizacao()
{
    // Submenu para modificar o valor
    switch (sub_menu)
    {
        case 1:
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)"< PARAMETRIZACAO >");
            setCursor(&lcd, 0, 1);
            char buffer[16];
            snprintf(buffer, sizeof(buffer), "SENHA:     %d ", current_value);
            print(&lcd, (int8_t *)buffer);
            break;

        case 2:
            // Atualiza o display com o valor atual
            setCursor(&lcd, 0, 0);
            print(&lcd, (int8_t *)" PARAMETRIZACAO ");
            setCursor(&lcd, 0, 1);
            snprintf(buffer, sizeof(buffer), "   Ano:    %d   ", current_value);
            print(&lcd, (int8_t *)buffer);
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
