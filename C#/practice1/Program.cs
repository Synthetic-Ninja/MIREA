using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Text.RegularExpressions;


// Получение документа
JObject get_document(string path_to_json)
{
	JObject jObject;
	using (var sr = new StreamReader(path_to_json))
	{
		var reader = new JsonTextReader(sr);
		jObject = JObject.Load(reader);
	}
	return jObject;
}


// _____________________________________________Задание 1______________________________________________________
void Func1(JObject jObject)
{

	var contents = jObject["content"]["section4"]["professionalStandards"].Select(p => p);
	Console.WriteLine(("").PadRight(80, '-'));
	foreach (var content in contents)
	{	
		var str_content = content["content"].ToString();
		Regex regex = new Regex(@"^\d{1,2}.\d{1,3}");
		MatchCollection matches = regex.Matches(str_content);
		if (matches.Count > 0)
		{
			string[] printed_str_content = str_content.Split(' ');
			Console.WriteLine("| {0} | {1} ", printed_str_content[0], string.Join(" ", printed_str_content[1..]));
			Console.WriteLine(("").PadRight(80, '-'));
		}

	}

}


// _____________________________________________Задание 2______________________________________________________
void Func2(JObject jObject)
{
	var competencyrows = jObject["content"]["section4"]["universalCompetencyRows"].Select(p => p);
	Console.Write("Введите код компетенции: ");
    string competencyCode = Console.ReadLine() + '.';

	
    IEnumerable<JToken>[] competencylist = {
    										jObject["content"]["section4"]["universalCompetencyRows"].Select(p => p),
    						  				jObject["content"]["section4"]["commonCompetencyRows"].Select(p => p)
    						  			   };
	foreach (var jobject in competencylist)
	{
		foreach (var competency in jobject)
		{		
			
			var competency_name = competency["competence"]["code"];
			if (competency_name.ToString() == competencyCode)
			{
				Console.WriteLine(("").PadRight(80, '-'));
				var competency_title = competency["competence"]["title"];
				Console.WriteLine("| {0}| {1} ", competency_name, competency_title);
				Console.WriteLine(("").PadRight(80, '-'));
				foreach (var indicator in competency["indicators"])
				{
					string[] splitted_content = indicator["content"].ToString().Split(":");
					Console.WriteLine("| {0}| {1}", splitted_content);
					Console.WriteLine(("").PadRight(80, '-'));
				}
				return;

			}

		}
	}

	Console.WriteLine("Компетенция '{0}' не найдена", competencyCode);
}


// _____________________________________________Задание 3______________________________________________________
void Func3(JObject jObject)
{

	Console.Write("Введите индекс дисциплины в формате 'Б1.Б.Д1': ");
    string disciplineIndex = Console.ReadLine();
    Console.WriteLine();
    
    var disciplines = jObject["content"]["section5"]["eduPlan"]["block1"]["subrows"].Select(p => p);
    foreach (var discipline in disciplines)
    {
     	var discipline_name = discipline["index"].ToString();
     	if (disciplineIndex == discipline_name)
     	{

			Console.WriteLine(("").PadRight(80, '-'));
			Console.WriteLine("| {0}| {1}| ", discipline_name, discipline["title"]);
			Console.WriteLine(("").PadRight(80, '-'));
			// Очистка от тегов и.т.д.
			Regex regex = new Regex(@"(\<(/?[^>]+)>)");
			string clean_description = regex.Replace(discipline["description"].ToString(), "");
			Console.WriteLine("| {0}| {1}", "Цель", clean_description);
			Console.WriteLine(("").PadRight(80, '-'));
			//Парсинг компетенций
			var competences = discipline["competences"].Select(p => p);
			var competences_list = new List<string>();
			foreach (var competence in competences)
                {   
                    competences_list.Add(string.Format("{0}, ", competence["code"].ToString()[..^1]));
                }
            Console.WriteLine("| {0}| {1}", "Компетенции", string.Join(" ", competences_list));
            Console.WriteLine(("").PadRight(80, '-'));
			
			Console.WriteLine("| {0} | {1} ","З.Е.", discipline["unitsCost"]);
			Console.WriteLine(("").PadRight(80, '-'));
			var terms = discipline["terms"];
			var semesters = new List<string>();
			foreach (var term in terms)
            {
            	semesters.Add(term.ToObject<bool>() == true ? "✓" : "x");
            }

            Console.WriteLine("| {0} | {1} ","Семестры", string.Join(" ", semesters));

     	}
                

    }

}


// _____________________________________________Задание 4______________________________________________________
void Func4(JObject jObject)
{
	Console.Write("Выберите семестр из списка пример:'1, 2, 3, 4, 5, 6, 7, 8': ");
    string term = Console.ReadLine();
    Console.WriteLine();
    Console.WriteLine(("").PadRight(80, '-'));
    Console.WriteLine("| Шифр | Название дисциплины |");
    Console.WriteLine(("").PadRight(80, '-'));
    var disciplines = jObject["content"]["section5"]["eduPlan"]["block1"]["subrows"].Select(p => p);
    foreach (var discipline in disciplines)
    {
    	var terms = discipline["terms"].Select(p => p);
    	JArray termsArray = new JArray(terms);
        if (termsArray[int.Parse(term) - 1].ToObject<bool>())
        {
        	Console.WriteLine("| {0} | {1} |", discipline["index"], discipline["title"]);
        	Console.WriteLine(("").PadRight(80, '-'));
    	}
    }

}


// _____________________________________________Задание 5______________________________________________________
void Func5(JObject jObject)
{
	Console.Write("Введите курс пример: '1' : ");
    string course = Console.ReadLine();
    Console.Write("Введите год начала обучения: ");
    string start_year = Console.ReadLine();
    Console.WriteLine();
	var studying_types = new Dictionary<string, string>()
	            {
	                { "Б1", "Теоретическое обучение" },
	                { "Б2", "Практика" },
	                { "Э", "Промежуточная аттестация"},
	                { "К", "Каникулы" },
	                { "У", "Учебная практика" },
	                { "П", "Производственная практика" },
	                { "НИР", "Научно-исследовательская работа" },
	                { "Д", "Государственная итоговая аттестация" }
	            };

    var courses = jObject["content"]["section5"]["calendarPlanTable"]["courses"].Select(p => p);
    JArray courses_array = new JArray(courses);

    var weeks = courses_array[int.Parse(course) - 1]["weekActivityIds"].Select(p => p);
    JArray weeks_array = new JArray(weeks);
    DateTime start_date = new DateTime(int.Parse(start_year) + int.Parse(course) - 1, 9, 1);
    DateTime end_date = new DateTime();
    int weeks_amount = 0;
    string current_studying_type = weeks_array[0].ToString();

    for (int i = 0; i < weeks_array.Count; i++)
	{
		
		 if (i == weeks_array.Count - 1){
		 	weeks_amount++;
		 	end_date = start_date.AddDays(weeks_amount * 7);
            while (end_date.DayOfWeek != DayOfWeek.Saturday)
            	end_date = end_date.AddDays(-1);

            Console.WriteLine("| {0} | {1}-{2} | {3} |", studying_types[current_studying_type],
														 start_date.ToString("dd.MM.yyyy"),
														 end_date.ToString("dd.MM.yyyy"),
														 weeks_amount);
            return;

		 }

		if (weeks_array[i].ToString() != current_studying_type)
		{
			end_date = start_date.AddDays(weeks_amount * 7);
            while (end_date.DayOfWeek != DayOfWeek.Saturday)
                end_date = end_date.AddDays(-1);


			Console.WriteLine("| {0} | {1}-{2} | {3} |", studying_types[current_studying_type],
														 start_date.ToString("dd.MM.yyyy"),
														 end_date.ToString("dd.MM.yyyy"),
														 weeks_amount);
			weeks_amount = 1;
			current_studying_type = weeks_array[i].ToString();
			start_date = end_date.AddDays(2);
		}

	weeks_amount++;

    }

}



// ___________________________MAIN__________________________________

void main_func()
{

	var file = get_document("2.json");
	Console.WriteLine("Введите номер задания 1-5\n: ");
	string answer = Console.ReadLine();

	switch (answer)
	{
		case "1":
			Func1(file);
			break;
		case "2":
			Func2(file);
			break;
		case "3":
			Func3(file);
			break;
		case "4":
			Func4(file);
			break;
		case "5":
			Func5(file);
			break;

		default:
		Console.WriteLine("Номер не найден.");
		break;
	}
	Console.WriteLine("Для продолжения нажмите Enter...");
	Console.ReadLine();

}


main_func();




