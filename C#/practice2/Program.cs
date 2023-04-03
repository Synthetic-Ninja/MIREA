using System.Collections.Generic;
using System.Collections;
using Microsoft.EntityFrameworkCore;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Text.RegularExpressions;


namespace ConsoleApp.PostgreSQL
{
    

    // ______________CONTEXT CLASS______________

    public class RealtorSinayginContext : DbContext
    {
       
        public RealtorSinayginContext()
		{
			Database.EnsureCreated();
		}

		// Initializating Tables
		public DbSet<District> District { get; set; }
        public DbSet<Building_Material> Building_Material { get; set; }
        public DbSet<Object_Type> Object_Type { get; set; }
        public DbSet<Estate_Object> Estate_Object { get; set; }
        public DbSet<Rate_Criteria> Rate_Criteria { get; set; }
        public DbSet<Rate> Rate { get; set; }
		public DbSet<Realtor> Realtor { get; set; }
		public DbSet<Sale> Sale { get; set; }
        
		


		// Set settings for connection to postgreSQL
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)

//________________________________________SET BEFORE USING_______________________________________________________
            => optionsBuilder.UseNpgsql("Host='XXXXXX:5432;Database=XXXXXX;Username=XXXXXXX;Password=XXXXXXX");
    
    }

    // ______________TABLES CLASSES______________

    public class District
    {
    	public int Id { get; set; }
    	public string District_Name {get; set; }

    	// Navigation parameter
    	public List<Estate_Object> Estate_Objects { get; set; }


    }

    public class Building_Material
    {
    	public int Id { get; set; }
    	public string Material_Name { get; set; }

    	// Navigation parameter
    	public List<Estate_Object> Estate_Objects { get; set; }

    }

	
	public class Object_Type
	{
		public int Id { get; set; }
		public string Type_Name { get; set; }

		// Navigation parameter
    	public List<Estate_Object> Estate_Objects { get; set; }
	}    


    public class Estate_Object
    {
    	public int Id { get; set; }
    	
    	// Foreign key to District
    	public int DistrictId { get; set; }
    	public District District { get; set; }

    	public string Address { get; set; }
    	public int Floor { get; set; }
    	public int Rooms_Count { get; set; }
    	
    	
    	// Foreign key to object_type
    	public int Object_TypeId {get; set; }
    	public Object_Type Object_Type { get; set; }

    	public int Status { get; set; }
    	public double Price { get; set; }
    	public string Object_Discription { get; set; }
    	
    	
    	// Foreign key to building_material
    	public int Building_MaterialId {get; set; }
    	public Building_Material Building_Material { get; set; }

    	public double Area { get; set; }
    	public DateTime Created_Date { get; set; }


    	// Navigation parameters
    	public List<Rate> Rates { get; set; }
    	public List<Sale> Sales { get; set; }


    }

    public class Rate_Criteria
    {
    	public int Id { get; set; }
    	public string Criteria_Name { get; set; }

    	// Navigation parameter
    	public List<Rate> Rates { get; set; }

    }


    public class Rate
    {
    	public int Id { get; set; }
    	
    	// Foreign key to estate_objects
    	public int Estate_ObjectId { get; set; }
    	public Estate_Object Estate_Object { get; set; }

    	public DateTime Rate_Date { get; set; }

    	//Foreign key to criteria_rate
    	public int Rate_CriteriaId { get; set; }
    	public Rate_Criteria Rate_Criteria { get; set; }

    	public double Rate_Value { get; set; }

    }


    public class Realtor
    {
    	public int Id { get; set; }
    	public string Realtor_Last_Name { get; set; }
    	public string Realtor_First_Name { get; set; }
        public string Realtor_Middle_Name { get; set; }
    	public string Realtor_Phone { get; set; }

    	public List<Sale> Sale { get; set; }
    }


    public class Sale
    {
    	public int Id { get; set; }

		// Foreign key to estate_objects
    	public int Estate_ObjectId { get; set; }
    	public Estate_Object Estate_Object { get; set; }

    	public DateTime Sale_Date { get; set; }


    	// Foreign key to realtor
    	public	int RealtorId { get; set; }
    	public Realtor Realtor { get; set; }

    	public double Price { get; set; }
    }

    class BaseGenerator
    {
        private RealtorSinayginContext Base;
        private JObject Json;
        
        public BaseGenerator(RealtorSinayginContext InputBase)
        {
            Base = InputBase;
            Json = get_document("data.json");

        }

        public void GenDisctricts()
        {
            var DistrictsList = Json["districts"].Select(p => p.ToString()).ToList();
            foreach (string district in DistrictsList)
            {
                var CurrentDistrict = new District{District_Name = district};
                Base.Add(CurrentDistrict);
                Base.SaveChanges();
            }


        }

        public void GenBuildungMaterials()
        {
            var BuildingMaterialsList = Json["buidlind_materials"].Select(p => p.ToString()).ToList();
            foreach (string building_material in BuildingMaterialsList)
            {
                var CurrentBuildingMaterial = new Building_Material{Material_Name = building_material};
                Base.Add(CurrentBuildingMaterial);
                Base.SaveChanges();
            }
 

        }

        public void GenObjectType()
        {
            var ObjectTypesList = Json["objects_type"].Select(p => p.ToString()).ToList();
            foreach (string objects_type in ObjectTypesList)
            {
                var CurrentObjectType = new Object_Type{Type_Name = objects_type};
                Base.Add(CurrentObjectType);
                Base.SaveChanges();
            }


        }

        private int get_random_int_item(List<int> ItemList)
        {
            var rand = new Random();
            return ItemList[rand.Next(ItemList.Count)];

        }

        private JObject get_document(string path_to_json)
        {
            JObject jObject;
            using (var sr = new StreamReader(path_to_json))
            {
                var reader = new JsonTextReader(sr);
                jObject = JObject.Load(reader);
            }
            return jObject;
        }


        public void GenObjects(int obj_count)
        {
            //Initialize random
            var rand = new Random();

            // Getting list with districts codes
            List<int> DistrictsList = new List<int>();

            foreach(District obj in Base.District.ToList())
            {
                DistrictsList.Add(obj.Id);
            }


            // Getting list with bulding_materials codes
            List<int> BuildingMaterialsList = new List<int>();
            
            foreach(Building_Material obj in Base.Building_Material.ToList())
            {
                BuildingMaterialsList.Add(obj.Id);
            }

            // Getting list with object_types codes
            List<int> ObjectTypesList = new List<int>();

            int min_price = 7000000;
            int max_price = 100000000;

            DateTime end_date = new DateTime(2022, 1, 1);
            DateTime start_date = new DateTime(2015, 1, 1);


            foreach(Object_Type obj in Base.Object_Type.ToList())
            {
                ObjectTypesList.Add(obj.Id);
            }


            //Generating objects
            for (int i = 0; i < obj_count; i++)
            {
                int CurrentDistrict = get_random_int_item(DistrictsList);
                int CurrentBuildingMaterial = get_random_int_item(BuildingMaterialsList);
                int CurrentObjectType = get_random_int_item(ObjectTypesList);
                
                

                // Check for object type is house
                int CurrentFloor;
                if (CurrentObjectType == 2)
                {
                    CurrentFloor = 1;    
                }
                else
                {
                    CurrentFloor = rand.Next(1, 15);
                }

                int CurrentRoomsCount = rand.Next(1, 5);
                int CurrentStatus = 1;
                double CurrentArea = rand.NextDouble() * ((150 - 20) + 20);
                double CurrentPrice = rand.NextDouble() * ((max_price - min_price) + min_price);

                //Get created_date
                
                int date_range = (end_date - start_date).Days;
                DateTime CurrentDate = start_date.AddDays(rand.Next(date_range));


                //Get street_string from json file
                var streets = Json["streets"].Select(p => p.ToString()).ToList();

                string CurrentAddress = streets[rand.Next(streets.Count)];

                //Get descriptons from json file
                var descriptions = Json["descriptions"].Select(p => p.ToString()).ToList();

                string CurrentDescription = descriptions[rand.Next(descriptions.Count)];

                // Creating Estate_Object
                var CurrentEstateObject = new Estate_Object{
                                                            DistrictId = CurrentDistrict,
                                                            Address = CurrentAddress,
                                                            Floor = CurrentFloor,
                                                            Rooms_Count = CurrentRoomsCount,
                                                            Object_TypeId = CurrentObjectType,
                                                            Status = CurrentStatus,
                                                            Price = CurrentPrice,
                                                            Object_Discription = CurrentDescription,
                                                            Building_MaterialId = CurrentBuildingMaterial,
                                                            Area = CurrentArea,
                                                            Created_Date = CurrentDate.ToUniversalTime()
                                                            };
                Base.Add(CurrentEstateObject);
                Base.SaveChanges();

            }
        }

        public void GenRatesCritery()
        {
            var RateCriteries = Json["criterias"].Select(p => p.ToString()).ToList();

            for (int i = 0; i < RateCriteries.Count; i++){
                var CurrentRateCriteria = new Rate_Criteria{Criteria_Name = RateCriteries[i]};
                Base.Add(CurrentRateCriteria);
                Base.SaveChanges();
            }

        }

        public void GenRates()
        {
            
            var rand = new Random();

            int min_rate = 1; 
            int max_rate = 5;

            //Get all estate_objects
            var EstateObjectsList = Base.Estate_Object.ToList();

            //Get all ratecriterias
            List<int> RateCriteriasList = new List<int>();

            foreach(Rate_Criteria obj in Base.Rate_Criteria.ToList())
            {
                RateCriteriasList.Add(obj.Id);
            }

            for (int i = 0; i < EstateObjectsList.Count; i++)
            {
                DateTime ObjectCreatedDate = EstateObjectsList[i].Created_Date;
                int CurrentEstateObject = EstateObjectsList[i].Id;
                
                for (int j = 0; j < RateCriteriasList.Count; j++)
                {
                    int CurrentRateCriteria = RateCriteriasList[j];
                    DateTime CurrentRateDate = ObjectCreatedDate.AddDays(rand.Next(10, 366));
                    double CurrentRateValue = (double)rand.Next(min_rate * 10, max_rate * 10)/10f;
                    var CurrentRate = new Rate{ 
                                                Estate_ObjectId = CurrentEstateObject,
                                                Rate_Date = CurrentRateDate,
                                                Rate_CriteriaId = CurrentRateCriteria,
                                                Rate_Value = CurrentRateValue
                                              };
                    Base.Add(CurrentRate);
                    Base.SaveChanges();

                }
            }
        }

        public void GenReators()
        {
            
            foreach (var realtor in Json["realtors"])
            {
                var CurrentRealtorLastName = realtor["last_name"].ToString();
                var CurrentRealtorFirstName = realtor["first_name"].ToString();
                var CurrentRealtorMiddleName = realtor["middle_name"].ToString();
                var CurrentRealtorPhone = realtor["phone"].ToString();

                var CurrentRealtor = new Realtor{Realtor_Last_Name = CurrentRealtorLastName,
                                                 Realtor_First_Name = CurrentRealtorFirstName,
                                                 Realtor_Middle_Name = CurrentRealtorMiddleName,
                                                 Realtor_Phone = CurrentRealtorPhone
                                                 };
                Base.Add(CurrentRealtor);
                Base.SaveChanges();
            }
        }

        public void GenSales(int sales_count)
        {
            var rand = new Random();

            int min_price = 200000;
            int max_price = 2000000;

            var EstateObjectsList = Base.Estate_Object.Where(p => p.Status == 1).ToList();
            int EstateObjectsLen = EstateObjectsList.Count;
            var RealtorsId = Base.Realtor.Select(p => p.Id).ToList();
            sales_count = EstateObjectsLen < sales_count ? EstateObjectsLen : sales_count;
            Console.WriteLine("Available count sales: {0}", sales_count);        
            for (int i = 0; i < sales_count; i++){
                EstateObjectsList[i].Status = 0;
                Base.SaveChanges();
                int CurrentObjectId = EstateObjectsList[i].Id;
                DateTime SaLeDate = EstateObjectsList[i].Created_Date.AddDays(rand.Next(30, 365));
                int CurrentRealtor = get_random_int_item(RealtorsId);
                double SalePrice = EstateObjectsList[i].Price + (rand.NextDouble() * (max_price - min_price) + min_price);

                var CurrentSale = new Sale{
                                            Estate_ObjectId = CurrentObjectId,
                                            Sale_Date = SaLeDate,
                                            RealtorId = CurrentRealtor,
                                            Price = SalePrice
                                          };
                Base.Add(CurrentSale);
                Base.SaveChanges();
            }
        
        }

    }
    //Practice class
    public class Practice
    {
        private RealtorSinayginContext Base;

        public Practice(RealtorSinayginContext db)
        {
            Base = db;
        }


        public void Question1(string district_name, double min_price, double max_price)
        {
            var QueryObjects = (from obj in Base.Estate_Object
                                where obj.District.District_Name == district_name && obj.Price > min_price && obj.Price < max_price 
                                select obj).ToList();
           
           foreach (var Object in QueryObjects)
                Console.WriteLine("|{0} | {1} | {2}|", Object.Address, Math.Round(Object.Area, 2), Object.Floor);
        }

        public void Question2(int rooms)
        {
            var QueryObjects = Base.Realtor.Join(Base.Sale,
                                                 r => r.Id,
                                                 s => s.RealtorId,
                                                 (r, s) =>  new {r, s})
                                                .Where(eo => eo.s.Estate_Object.Rooms_Count == rooms)
                                                .Select(eo => eo.r)
                                                .ToList();


            foreach (var Object in QueryObjects)
                Console.WriteLine("{0} {1} {2}", Object.Realtor_Last_Name, Object.Realtor_First_Name, Object.Realtor_Middle_Name);

        }


        public void Question3(int floor)
        {
            var QueryObjects = from sale in Base.Sale
                               join obj in Base.Estate_Object on sale.Estate_ObjectId equals obj.Id
                               join realt in Base.Realtor on sale.RealtorId equals realt.Id
                               where obj.Floor == floor
                               select new {
                                           Address = obj.Address,
                                           ObjPrice = obj.Price,
                                           SalePrice = sale.Price,
                                           LastName = realt.Realtor_Last_Name,
                                           FirstName = realt.Realtor_First_Name,
                                           MiddleName = realt.Realtor_Middle_Name
                                           };
                                                

            Console.WriteLine("Все объекты на {0} этаже", floor);
            Console.WriteLine("---------------------------------------------");
            foreach (var QueryObject in QueryObjects)
            {
                
                Console.WriteLine("Адрес: {0}|\nРазница: {1}|\nФио: {2} {3} {4}|",
                                  QueryObject.Address,
                                  QueryObject.SalePrice - QueryObject.ObjPrice,
                                  QueryObject.LastName,
                                  QueryObject.FirstName,
                                  QueryObject.MiddleName
                                  );
                Console.WriteLine("---------------------------------------------");
            }
        }

        public void Question4(string district_name, int rooms_count)
        {
            var QueryObjects = Base.Estate_Object.Join(Base.District,
                                                       obj => obj.DistrictId,
                                                       ds => ds.Id ,
                                                       (obj, ds) => new {obj, ds})
                                                       .Where(eo => eo.obj.Rooms_Count == rooms_count && eo.ds.District_Name == district_name)
                                                       .Select(eo => eo.obj.Price)
                                                       .Sum();

            Console.WriteLine("Сумма всех квартир в районе: '{0}' и кол-вом комнат: {1}\n: {2}", district_name, rooms_count, QueryObjects);                                               
        
        }

        public void Question5(string realtor_last_name)
        {
            var QueryObjects = Base.Sale.Join(Base.Realtor,
                                              s => s.RealtorId,
                                              r => r.Id,
                                              (s, r) => new {s, r})
                                              .Where(all => all.r.Realtor_Last_Name == realtor_last_name)
                                              .Select(all => all.s.Price);
            
            Console.WriteLine("Фамилия реалтора {0}\nМинимальная цена: {1}\nМаксимальная цена: {2}",
                               realtor_last_name,
                               QueryObjects.Min(),
                               QueryObjects.Max());

        }

        public void Question6(string district_name)
        {
            var QueryObjects = Base.Estate_Object.Join(Base.District,
                                                       obj => obj.DistrictId,
                                                       dist => dist.Id,
                                                       (obj, dist) => new{obj, dist})
                                                 .Join(Base.Rate,
                                                       all => all.obj.Id,
                                                       rt => rt.Estate_ObjectId,
                                                       (all, rt) => new{all, rt})
                                                 .Where(allq => allq.all.dist.District_Name == district_name)
                                                 .Average(allq => allq.rt.Rate_Value);


            Console.WriteLine("Средняя оценка для объектов в районе : {0}\n: {1:f2}", district_name, QueryObjects);

        }

        public void Question7(int floor)
        {
            var QueryObjects = Base.Estate_Object.Join(Base.District,
                                                       obj => obj.DistrictId,
                                                       dist => dist.Id,
                                                       (obj, dist) => new{obj, dist})
                                                       .Where(p => p.obj.Floor == floor)
                                                       .GroupBy(all => all.dist.District_Name)
                                                       .Select(eo => new{DsName = eo.Key, Count = eo.Count()});
           
           foreach (var QueryObject in QueryObjects)                                            
           Console.WriteLine("{0} --- {1}", QueryObject.DsName, QueryObject.Count);
        }

        public void Question8(string criteria_name, string object_type_name, string realtor_last_name)
        {
            var QueryObjects = from sale in Base.Sale
                               join obj in Base.Estate_Object on sale.Estate_ObjectId equals obj.Id
                               join tp in Base.Object_Type on obj.Object_TypeId equals tp.Id
                               join realt in Base.Realtor on sale.RealtorId equals realt.Id
                               join rt in Base.Rate on obj.Id equals rt.Estate_ObjectId 
                               join ct_rt in Base.Rate_Criteria on rt.Rate_CriteriaId  equals ct_rt.Id  
                               where ct_rt.Criteria_Name == criteria_name 
                               && realt.Realtor_Last_Name == realtor_last_name 
                               && tp.Type_Name == object_type_name                        
                               select new {rate = rt.Rate_Value};

            
            

            Console.WriteLine("Средняя оценка по критерию: {0}\nОбъекта типа: {1}\nПроданных реалтором {2}\nОценка: {3}", 
                               criteria_name,
                               object_type_name,
                               realtor_last_name,
                               QueryObjects.Average(p => p.rate));
        }

        public void Question9(DateTime min_date, DateTime max_date)
        {
            var QueryObjects = from sale in Base.Sale
                               join obj in Base.Estate_Object on sale.Estate_ObjectId equals obj.Id
                               where sale.Sale_Date > min_date.ToUniversalTime() && sale.Sale_Date < max_date.ToUniversalTime()
                               select new {id = obj.Id, price = sale.Price, area = obj.Area};


            Console.WriteLine("Объекты проданные в диапазоне {0} - {1}", min_date, max_date);
            Console.WriteLine("---------------------------------------------");
            foreach (var QueryObject in QueryObjects)
            {
                Console.WriteLine("Id Квартиры: {0}\nСредняя продажная стоиомость: {1}", QueryObject.id, QueryObject.price / QueryObject.area);
                Console.WriteLine("---------------------------------------------");
            }
        }

        public void Question10()
        {
            var realtorslist = Base.Realtor.Select(p => new{id = p.Id,
                                                            last_name = p.Realtor_Last_Name,
                                                            first_name = p.Realtor_First_Name,
                                                            middle_name = p.Realtor_Middle_Name});


            
            var QueryObjects = Base.Sale.Join(Base.Realtor,
                                              s => s.RealtorId,
                                              r => r.Id,
                                              (s, r) => new {s, r}).GroupBy(p => new {p.r.Id})
                                              .Select(eo => new {realt = eo.Key, count = eo.Count(), sum = eo.Sum(p=> p.s.Price)}).ToList();

            foreach (var realtor in realtorslist)
            {
                var LastName = realtor.last_name;
                var FirstName = realtor.first_name;
                var MiddleName = realtor.middle_name;
                var obj = QueryObjects.Where(p => p.realt.Id == realtor.id);
                string all_sum;
                if (obj.Count() != 0)
                {
                    var bonus_sum = obj.First().count * obj.First().sum * 0.05;
                    all_sum = (bonus_sum - bonus_sum * 0.13).ToString();
                }
                else
                {
                    all_sum = "Реэлтор ничего не продал.";
                }

                Console.WriteLine("{0} {1} {2} | {3}" , LastName, FirstName, MiddleName, all_sum);
            }
        
        }

        public void Question11()
        {
            var realtorslist = Base.Realtor.Select(p => new{id = p.Id,
                                                            last_name = p.Realtor_Last_Name,
                                                            first_name = p.Realtor_First_Name,
                                                            middle_name = p.Realtor_Middle_Name});


            
            var QueryObjects = Base.Sale.Join(Base.Realtor,
                                              s => s.RealtorId,
                                              r => r.Id,
                                              (s, r) => new {s, r}).GroupBy(p => new {p.r.Id})
                                              .Select(eo => new {realt = eo.Key, count = eo.Count()}).ToList();

            foreach (var realtor in realtorslist)
            {
                var LastName = realtor.last_name;
                var FirstName = realtor.first_name;
                var MiddleName = realtor.middle_name;
                var obj = QueryObjects.Where(p => p.realt.Id == realtor.id);
                Console.WriteLine("{0} {1} {2} | {3}" , LastName, FirstName, MiddleName, obj.Count() != 0? obj.First().count : "Реэлтор ничего не продал.");
            }
        }


        public void Question12(int floor)
        {
            var QueryObjects = Base.Estate_Object.Join(Base.Building_Material,
                                                       s => s.Building_MaterialId,
                                                       r => r.Id,
                                              (s, r) => new {s, r})
                                              .Where(p => p.s.Floor == floor)
                                              .GroupBy(p => new {p.r.Id , p.r.Material_Name})
                                              .Select(eo => new {bm = eo.Key, av = eo.Average(p=> p.s.Price)}).ToList();
            foreach (var QueryObject in QueryObjects)
            {
                Console.WriteLine("{0} - {1}", QueryObject.bm.Material_Name, QueryObject.av);
            }

        }
        

        public void Question13()
        {
            var QueryObjects = Base.Estate_Object.OrderByDescending(u => u.Price)
                                                 .ThenBy(u => u.Floor)
                                                 .Select(eo => new { ds_id = eo.District.Id ,
                                                                     ds_name = eo.District.District_Name,
                                                                     obj_addr = eo.Address,
                                                                     obj_price = eo.Price,
                                                                     obj_floor = eo.Floor});

            var district_dict = new Dictionary<int, int>();

            var districts = Base.District.Select(p => p.Id);

            foreach (var distr in districts)
            {
                district_dict.Add(distr, 0);
            }

            foreach (var QueryObject in QueryObjects)
            {
                if (district_dict[QueryObject.ds_id] >= 3) continue;

                district_dict[QueryObject.ds_id] ++;
                Console.WriteLine("Название района: {0}| Адрес: {1}| Стоимость: {2}| Этаж: {3}",
                                  QueryObject.ds_name,
                                  QueryObject.obj_addr,
                                  QueryObject.obj_price,
                                  QueryObject.obj_floor);
                Console.WriteLine("------------------------------");
            }

        }



        public void Question14(string district_name)
        {
            var QueryObjects = Base.Estate_Object.Where(s => s.District.District_Name == district_name && s.Status != 0).Select(s => s.Address);

            
            Console.WriteLine("Непроданные квартиры в районе {0}", district_name);
            Console.WriteLine("------------------------------");
            foreach(var QueryObject in QueryObjects)
            {
                Console.WriteLine(QueryObject);
            }
        }

        public void Question15(string district_name)
        {
            var QueryObjects = Base.Sale.Where(s => s.Estate_Object.District.District_Name == district_name
                                               && ((s.Price - s.Estate_Object.Price) / s.Estate_Object.Price * 100) <= 20)
                                        .Select(s => s.Estate_Object.Address);
        
            foreach (var QueryObject in QueryObjects)
            {
                Console.WriteLine("Адрес : {0} | Район : {1}", QueryObject, district_name);
            }


        }

       public void Question16(string realtor_last_name)
       {
            var QueryObjects = Base.Sale.Where(s => s.Realtor.Realtor_Last_Name == realtor_last_name
                                               && ((s.Price - s.Estate_Object.Price) > 100000))
                                        .Select(s => new {addr = s.Estate_Object.Address, ds = s.Estate_Object.District.District_Name});

            
            Console.WriteLine("Продажи реэлтора: {0}", realtor_last_name);
            Console.WriteLine("------------------------------");
            foreach (var QueryObject in QueryObjects)
            {
                Console.WriteLine("Адрес : {0} | Район : {1}", QueryObject.addr, QueryObject.ds);
            }

       }

       public void Question17(DateTime year, string realtor_last_name)
       {
            var QueryObjects = Base.Sale.Where(s => s.Realtor.Realtor_Last_Name == realtor_last_name && s.Sale_Date.Year == year.Year)
                                        .Select(s => new {addr = s.Estate_Object.Address,
                                                obj_price = s.Estate_Object.Price,
                                                sale_price = s.Price});
            Console.WriteLine("Продажи реэлтора: {0}. В году {1}", realtor_last_name, year.Year);
            Console.WriteLine("------------------------------");
            foreach (var QueryObject in QueryObjects)
            {
                Console.WriteLine("Адрес: {0}, Разница {1:f2}%", QueryObject.addr, (QueryObject.sale_price - QueryObject.obj_price)/QueryObject.obj_price * 100);
            }

       }

       public void Question18()
       {
            
            var QueryObjects = Base.Estate_Object.Where(p => (p.Price / p.Area) < (Base.Estate_Object.Where(j => j.District.Id == p.District.Id).Average(j => j.Price / j.Area))).Select(p => p.Address);

            foreach (var QueryObject in QueryObjects){
            Console.WriteLine(QueryObject);}

       }


       public void Question19(DateTime year)
       {
            var saled_realtors = Base.Sale.Join(Base.Realtor,
                                              s => s.RealtorId,
                                              r => r.Id,
                                              (s, r) => new {s, r})
                                              .Where(eo => eo.s.Sale_Date.Year == year.Year)
                                              .Select(eo => eo.r);

            var QueryObjects = Base.Realtor.Except(saled_realtors).ToList();

            
            Console.WriteLine("Реэлторы которые не продали в {0} году: ", year.Year);
            if (QueryObjects.Count() == 0)
            {
                Console.WriteLine("Нет реэлторов, которые ничего не продали");
                return;
            }

            foreach (var QueryObject in QueryObjects)
            {
                Console.WriteLine("{0} {1} {2}", QueryObject.Realtor_Last_Name, QueryObject.Realtor_First_Name, QueryObject.Realtor_Middle_Name);
            }
       
       }

       public void Question20(DateTime now_date)
       {
            var utc_now_date = now_date.ToUniversalTime();
            
            var QueryObjects =  Base.Estate_Object.Where(p => (((utc_now_date.Year * 12 + utc_now_date.Month) - (p.Created_Date.Year * 12 + p.Created_Date.Month)) <= 4)
                                                              && ((p.Price / p.Area) < (Base.Estate_Object.Where(j => j.District.Id == p.District.Id).Average(j => j.Price / j.Area))))
                                                  .Select(p => new {addr = p.Address, stat = p.Status});

            foreach (var QueryObject in QueryObjects)
            {
                Console.WriteLine("Адрес: {0} | Статус: {1}", QueryObject.addr, QueryObject.stat == 0 ? "Продано" : "В продаже");
            }


       }







        
    }

    // ________________________MAIN PROGRAM__________________________
    internal class Program
    {
    	
        static void GenerateBase(RealtorSinayginContext dbcontext)
        {
            Console.WriteLine("Getting Basegenerator...");
                BaseGenerator BaseGen =  new BaseGenerator(dbcontext);
                Console.WriteLine("1.Generating Districts.");
                BaseGen.GenDisctricts();
                Console.WriteLine("2.Generating Object_Types.");
                BaseGen.GenObjectType();
                Console.WriteLine("3.Generating Building_Materials.");
                BaseGen.GenBuildungMaterials();
                Console.WriteLine("4.Generating Estate_Objects.");
                BaseGen.GenObjects(30);
                Console.WriteLine("5.Generating RateCriterias.");
                BaseGen.GenRatesCritery();
                Console.WriteLine("6.Generating Rates.");
                BaseGen.GenRates();
                Console.WriteLine("7.Generating Realtors.");
                BaseGen.GenReators();
                Console.WriteLine("8.Generating Sales.");
                BaseGen.GenSales(15);
                Console.WriteLine("Success!");
        }


        static void RunQuestions(RealtorSinayginContext db)
        {
            
            Practice practice = new Practice(db);
            while (true)
            {
                Console.Write("Введите номер задания или 0 для выхода. : ");
                var answer = Console.ReadLine();
                Console.WriteLine("\n");

                switch (answer)
                {
                    case "0":
                        Console.WriteLine("Выход..");
                        return;

                    case "1":
                        Console.WriteLine("Вывести объекты недвижимости, расположенные в указанном районе стоимостью «ОТ» и «ДО»\n");
                        practice.Question1("Зеленоград", 0, 200000000);
                        break;

                    case "2":
                        Console.WriteLine("Вывести фамилии риэлтор, которые продали двухкомнатные объекты недвижимости\n");
                        practice.Question2(2);
                        break;

                    case "3":
                        Console.WriteLine("Вывести разницу между заявленной и продажной стоимостью объектов недвижимости, расположенных на 2 этаже\n");
                        practice.Question3(2);
                        break;

                    case "4":
                        Console.WriteLine("Определить общую стоимость всех двухкомнатных объектов недвижимости, расположенных в указанном районе\n");
                        practice.Question4("Зеленоград", 1);
                        break;

                    case "5":
                        Console.WriteLine("Определить максимальную и минимальную стоимости объекта недвижимости, проданного указанным риэлтором\n");
                        practice.Question5("Ганичев");
                        break;

                    case "6":
                        Console.WriteLine("6. Определить среднюю оценку объектов недвижимости, расположенных в указанном районе\n");
                        practice.Question6("Зеленоград");
                        break;

                    case "7":
                        Console.WriteLine("Вывести информацию о количестве объектов недвижимости,расположенных на 2 этаже по каждому району\n");
                        practice.Question7(1);
                        break;

                    case "8":
                        Console.WriteLine("Определить среднюю оценку апартаментов по критерию «Безопасность», проданных указанным риэлтором\n");
                        practice.Question8("Безопасность", "Апартаменты", "Исаев");
                        break;

                    case "9":
                        Console.WriteLine("Определить среднюю продажную стоимость 1м2 для квартир, которые были проданы в указанную дату «ОТ» и «ДО»");
                        practice.Question9(new DateTime(2010, 1 ,1 ), new DateTime(2023, 1, 1));
                        break;

                    case "10":
                        Console.WriteLine("Вывести информацию о премии риэлтора");
                        practice.Question10();
                        break;

                    case "11":
                        Console.WriteLine("Вывести информацию о количестве квартир, проданных каждым риэлтором");
                        practice.Question11();
                        break;

                    case "12":
                        Console.WriteLine("Вывести информацию о средней стоимости объектов недвижимости, расположенных на 2 этаже по каждому материалу здания.\n");
                        practice.Question12(1);
                        break;

                    case "13":
                        Console.WriteLine("Вывести информацию о трех самых дорогих объектах недвижимости,расположенных в каждом районе.\n");
                        practice.Question13();
                        break;

                    case "14":
                        Console.WriteLine("Определить адреса квартир, расположенных в указанном районе, которые еще не проданы.\n");
                        practice.Question14("Зеленоград");
                        break;

                    case "15":
                        Console.WriteLine("Вывести информацию об объектах недвижимости, у которых разница между заявленной и продажной стоимостью составляет не более 20 % и расположенных в указанном районе.\n");
                        practice.Question15("Зеленоград");
                        break;

                    case "16":
                        Console.WriteLine("Вывести информацию об объектах недвижимости, у которых разница между заявленной и продажной стоимостью составляет больше 100000 рублей и проданную указанным риэлтором.\n");
                        practice.Question16("Ганичев");
                        break;

                    case "17":
                        Console.WriteLine("Вывести разницу в % между заявленной и продажной стоимостью для объектов недвижимости, проданных указанным риэлтором в текущем году.\n");
                        practice.Question17(new DateTime(2019, 1, 1), "Ганичев");
                        break;

                    case "18":
                        Console.WriteLine("Определить адреса квартир, стоимость 1м2 которых меньше средней по району.\n");
                        practice.Question18();
                        break;

                    case "19":
                        Console.WriteLine("Определить ФИО риэлторов, которые ничего не продали в текущем году.\n");
                        practice.Question19(new DateTime(2023, 1, 1));
                        break;

                    case "20":
                        Console.WriteLine("Вывести адреса объектов недвижимости, стоимость 1м2 которых меньше средней всех объектов недвижимости по району, объявления о которых были размещены не более 4 месяцев назад.");
                        practice.Question20(new DateTime(2021, 1, 1));
                        break;

                    default:
                        Console.WriteLine("Нверное значение попробуйте еще раз.\n");
                        break;

                }

                Console.WriteLine("\n\n");

            }
            
            
        }

        static void Main()
    	{
	    	bool CreateDb = false;
            int a;
            Console.WriteLine("Хотите ли вы заполнить базу? (Y/N)");
            while (true)
            {
                var Answer = Console.ReadLine().ToLower();

                if (Answer == "y")
                {
                    CreateDb = true;
                    break;
                }
                else if (Answer == "n")
                {
                    break;
                }

                Console.WriteLine("Неверное значение");

            }
            using (var db = new RealtorSinayginContext())
            {
                if (CreateDb) GenerateBase(db);
                RunQuestions(db);

                
            }
            Console.WriteLine("Программа завершена.");

    	}
    }
}

