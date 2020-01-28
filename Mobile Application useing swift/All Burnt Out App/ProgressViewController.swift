//
//  ProgressViewController.swift
//  Prancercise Tracker
//
//  Created by MCDONNELL, RYAN on 07/12/2018.

//

import Foundation
import HealthKit
import UIKit



class ProgressViewControler: UIViewController {
    
    var stepsCount = 0;
    var newDate = 0;
    
    @IBOutlet weak var DisplayStepsProgress: UIView!// progressbar for steps tacken
    @IBOutlet weak var DisplayStepsNeeded: UILabel!
    
 let healthStore = HKHealthStore()
    func getTodaysSteps(completion: @escaping (Double) -> Void) {
        
        let stepsQuantityType = HKQuantityType.quantityType(forIdentifier: .stepCount)!
        
        let now = Date()
        let startOfDay = Calendar.current.startOfDay(for: now)
        let predicate = HKQuery.predicateForSamples(withStart: startOfDay, end: now, options: .strictStartDate)
        
        let query = HKStatisticsQuery(quantityType: stepsQuantityType, quantitySamplePredicate: predicate, options: .cumulativeSum) { (_, result, error) in
            var resultCount = 0.0
            guard let result = result else {
                print("Failed to fetch steps rate")
                completion(resultCount)
                return
   
            }
            if let sum = result.sumQuantity() {
                resultCount = sum.doubleValue(for: HKUnit.count())
            }
            
            DispatchQueue.main.async {
                completion(resultCount)
            }
        }
        healthStore.execute(query)
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    func getTodaysFlights(completion: @escaping (Double) -> Void) {
        
        let flightsQuantityType = HKQuantityType.quantityType(forIdentifier: .flightsClimbed)!
        
        let now = Date()
        let startOfDay = Calendar.current.startOfDay(for: now)
        let predicate = HKQuery.predicateForSamples(withStart: startOfDay, end: now, options: .strictStartDate)
        
        let query2 = HKStatisticsQuery(quantityType: flightsQuantityType, quantitySamplePredicate: predicate, options: .cumulativeSum) { (_, result2, error) in
            var resultCount2 = 0.0
            guard let result2 = result2 else {
                print("Failed to fetch flights climbed")
                completion(resultCount2)
                return
                
            }
            if let sum = result2.sumQuantity() {
                resultCount2 = sum.doubleValue(for: HKUnit.count())
            }
            
            DispatchQueue.main.async {
                completion(resultCount2)
            }
        }
        healthStore.execute(query2)
                }
    
    @IBOutlet weak var outOfCalsLabel: UILabel!

    @IBOutlet weak var DisplayStepsTacken: UILabel!
    @IBOutlet weak var CaloriesBurntSteps: UILabel!

    @IBOutlet weak var ProgressBarTotal: UIProgressView!
    
    
    //Flights climbed
    @IBOutlet weak var DisplayFlightsClimbed: UILabel!
    @IBOutlet weak var CaloriesBurnedFlights: UILabel!
    @IBOutlet weak var FlightsNeeded: UILabel!
    
    //Totals
    @IBOutlet weak var TotalCaloriesLostLabel: UILabel!
    @IBOutlet weak var TotalCaloriesGainedLabel: UILabel!
    @IBOutlet weak var TotalLabel: UILabel!
    
    var  CalsSubtractionSteps = Float(0)
    var CalsSubtractionFlights = Float(0)
    var TotalCalsBurntSoFar = Float(0)
    

    
    @IBAction func GetStepsButton(_ sender: AnyObject? = nil) {
        
         let CalNumG = TaskVariables.CalNum // var thar holds the users target cal amount
        
        print("the global number:\(CalNumG)")
        
        outOfCalsLabel.text = "Out of \(CalNumG) calories"

        self.CalsSubtractionSteps = 0
        self.CalsSubtractionFlights = 0
        
        getTodaysSteps { (result) in
            
            let redultRounded = String(format: "%.0f", result)
            print("Todays steps done:\(redultRounded)")
            DispatchQueue.main.async {
                self.DisplayStepsTacken.text = "\(redultRounded)"
            }
            
            //sets the results of step progress by modifying the data recived from the healthkit to work out the current progress
             let totalCalsBurntSteps  = Float(result / 20)
             let WorkOutHowManyCaloriesleft = Float(CalNumG - (totalCalsBurntSteps + self.CalsSubtractionSteps))
            let workOutHowmanystepsneeded = Float(WorkOutHowManyCaloriesleft * 20 )
            
            self.CalsSubtractionFlights = self.CalsSubtractionFlights + totalCalsBurntSteps

            print("Total cals burnt steps:\(totalCalsBurntSteps)")
            DispatchQueue.main.async {
                self.CaloriesBurntSteps.text = "\(totalCalsBurntSteps)"
            }
            
            if(workOutHowmanystepsneeded > 0)
            {
                let workOutHowmanystepsneededRounded = String(format: "%.0f", workOutHowmanystepsneeded)
                print("Work out how many steps needed:\(workOutHowmanystepsneededRounded)")
        DispatchQueue.main.async {
            self.DisplayStepsNeeded.text = "\(workOutHowmanystepsneededRounded)"
                }
            }
                else
                {
                    print("\(0) steps needed")
                    DispatchQueue.main.async {
                        self.DisplayStepsNeeded.text = "Goal aquired, well done"
                          self.outOfCalsLabel.text = "Out of \(CalNumG) calories"
                    }
                }
            //-------------------------------------------------------------------------------------------------//
            self.getTodaysFlights { (result2) in
                let result2Rounded = String(format: "%.0f", result2)
                print("Todays flights done:\(result2Rounded)")
                DispatchQueue.main.async {
                    self.DisplayFlightsClimbed.text = "\(result2Rounded)"
                }
                
                //sets the results of flights climbed progress by modifying the data recived from the healthkit to work out the current progress
                let totalCalsBurntFlights = Float(result2 * 3.25)
                let WorkOutHowManyCaloriesleftFlights = Float(CalNumG - (totalCalsBurntFlights + self.CalsSubtractionFlights))
                let workOutHowmanyFlighsNeeded = Float(WorkOutHowManyCaloriesleftFlights / 3.25 )
                
                self.CalsSubtractionSteps = self.CalsSubtractionSteps + totalCalsBurntFlights
                
                let totalCalsBurntFlightsRounded = String(format: "%.2f", totalCalsBurntFlights)
                print("Total cals burnt flights:\(totalCalsBurntFlightsRounded)")
                DispatchQueue.main.async {
                    self.CaloriesBurnedFlights.text = "\(totalCalsBurntFlightsRounded)"
                }
                
                if(workOutHowmanyFlighsNeeded > 0)
                {
                    
                    let workOutHowmanyFlighsNeededRounded = String(format: "%.0f", workOutHowmanyFlighsNeeded)
                    print("Work out how many flights needed:\(workOutHowmanyFlighsNeededRounded)")
                    DispatchQueue.main.async {
                        self.FlightsNeeded.text = "\(workOutHowmanyFlighsNeededRounded)"
                    }
                }
                else
                {
                    print("\(0) steps needed")
                    DispatchQueue.main.async {
                        self.FlightsNeeded.text = "Goal aquired, well done"
                    }
                }
                //loading bar
                self.TotalCalsBurntSoFar = (self.CalsSubtractionSteps + self.CalsSubtractionFlights)
                
                let finalPercentage = Float(self.TotalCalsBurntSoFar / CalNumG)
               
                self.ProgressBarTotal.progress = finalPercentage
            
                print("Steps subtraction:\(self.CalsSubtractionSteps) & Flights Subtraction:\(self.CalsSubtractionFlights)")
                print("Final percentage:\(finalPercentage)")
                print("-----------------------------------------")
                
                //Totals
                self.TotalCaloriesLostLabel.text = "\(self.TotalCalsBurntSoFar)"
               self.TotalCaloriesGainedLabel.text = "\(TaskVariables.TotalCalNumGained)"
                
                let Total = Float(TaskVariables.TotalCalNumGained - self.TotalCalsBurntSoFar)
               
                if(Total <= 0)
                {
                    let Total2 = String(format: "%.2f", (Total - Total * 2))
                    self.TotalLabel.text = "You have lost: \(Total2) calories"
                }
                else if(Total >= 0)
                {
                    let TotalRoundedGained = String(format: "%.2f", Total)
                    self.TotalLabel.text = "You have Gained: \(TotalRoundedGained) calories"
                }
            }
        }
    }
    
    // this function chack to see if there is a shake and when it ends it will preform the update task so the user dosnt ned to press the button and it should update when in their pockets
    override func motionEnded(_ motion: UIEventSubtype, with event: UIEvent?) {
            self.GetStepsButton()
    }
}
    

