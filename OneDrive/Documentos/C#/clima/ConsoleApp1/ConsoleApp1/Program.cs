using System;
using System.Collections.Generic;
using System.Net.Http;
using Newtonsoft.Json;

namespace WeatherApp
{
    class Program
    {
        static async System.Threading.Tasks.Task Main(string[] args)
        {
            string apiKey = "3059583d8f5b189801e12b799fe03edd"; 

            Console.WriteLine("Digite o nome das cidades (separadas por vírgula): ");
            string cidadesInput = Console.ReadLine();

            string[] cidades = cidadesInput.Split(',');

            using (HttpClient client = new HttpClient())
            {
                try
                {
                    foreach (string cidade in cidades)
                    {
                        
                        string url = $"http://api.openweathermap.org/data/2.5/weather?q={cidade}&appid={apiKey}&units=metric";
                        HttpResponseMessage response = await client.GetAsync(url);
                        string responseBody = await response.Content.ReadAsStringAsync();

                        
                        WeatherData weatherData = JsonConvert.DeserializeObject<WeatherData>(responseBody);

                        
                        Console.WriteLine();
                        Console.WriteLine($"Cidade: {weatherData.Name}");

                        if (weatherData.Main != null)
                        {
                            Console.WriteLine($"Temperatura atual: {weatherData.Main.Temp}°C");
                        }
                        else
                        {
                            Console.WriteLine("Dados de temperatura indisponíveis.");
                        }

                        if (weatherData.Weather.Length > 0)
                        {
                            Console.WriteLine($"Condições climáticas: {weatherData.Weather[0].Description}");
                        }
                        else
                        {
                            Console.WriteLine("Dados de condições climáticas indisponíveis.");
                        }
                    }
                }
                catch (HttpRequestException)
                {
                    Console.WriteLine("Erro ao obter os dados de previsão do tempo.");
                }
            }

            Console.ReadLine();
        }
    }

   
    public class WeatherData
    {
        public string Name { get; set; }
        public MainData Main { get; set; }
        public Weather[] Weather { get; set; }
    }

    public class MainData
    {
        public float Temp { get; set; }
    }

    public class Weather
    {
        public string Description { get; set; }
    }
}
