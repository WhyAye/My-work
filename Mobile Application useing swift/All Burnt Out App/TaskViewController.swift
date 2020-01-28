//
//  TaskViewController.swift
//  Prancercise Tracker
//
//  Created by MCDONNELL, RYAN on 14/01/2019.

//

import UIKit

struct TaskVariables{
    static var CalNum = Float(0)
    static var TotalCalNumGained = Float(0)
}

class TaskViewController: UIViewController {
    @IBOutlet weak var WalkStepsLabel: UILabel!
    @IBOutlet weak var ClimbFlightsLabel: UILabel!
    @IBOutlet weak var ScrollView: UIScrollView!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    @IBOutlet weak var Calinputfield: UITextField!
    @IBOutlet weak var calInputWarning: UILabel!
    @IBOutlet weak var outOfCalsLabel: UILabel!
    
   
    
    
    
    @IBAction func setCalInput(_ sender: UIButton) {
        let CalNum: Float? = Float(Calinputfield.text!)
        if CalNum == nil
        {
            calInputWarning.text = "Please enter a whole number"
            return;
        }
        else
        {
            calInputWarning.text = ""
            let unWrap = Float(CalNum!)
            TaskVariables.CalNum = unWrap;
            let Warning = TaskVariables.CalNum
            outOfCalsLabel.text = "Out of \(Warning) calories"
            self.view.endEditing(true)
        }
        
        //update steps needed to compleate the task
        let GetCalsForNeededTotal = Float(CalNum!)
        
        let StepsNeededTotal = String(format: "%.0f",GetCalsForNeededTotal * 20)
        WalkStepsLabel.text = "Walk: \(StepsNeededTotal) Steps"
        
        let FlightsNeddedTotal = String(format: "%.0f", GetCalsForNeededTotal / 3.5)
        //let FlightsNeddedTotalRounded = String(format: "%.0f", FlightsNeddedTotal )
        ClimbFlightsLabel.text = "Climb: \(FlightsNeddedTotal) Flights of stairs"
        
        
    }
  

}
