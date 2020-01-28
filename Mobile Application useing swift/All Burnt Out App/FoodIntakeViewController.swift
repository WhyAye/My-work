//
//  FoodIntakeViewController.swift
//  Prancercise Tracker
//
//  Created by MCDONNELL, RYAN on 15/01/2019.

//

import UIKit

class FoodIntakeViewController: UIViewController {
    
    @IBOutlet weak var FoodNameInput: UITextField!
    @IBOutlet weak var AmmountOfCalsInput: UITextField!
    @IBOutlet weak var TotalCalsGainedLabel: UILabel!

    @IBOutlet weak var WarningLabel: UILabel!
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    @IBAction func AddToListButton(_ sender: UIButton) {

    // add the contence to the list here from the imput field
        let CalNumF: Float? = Float(AmmountOfCalsInput.text!)
        if CalNumF == nil
        {
            WarningLabel.text = "One of the fields above conains a invalid type"
            return;
        }
        else
        {
            AmmountOfCalsInput.text = ""
            WarningLabel.text = ""
            let unWrap = Float(CalNumF!)
            TaskVariables.TotalCalNumGained = TaskVariables.TotalCalNumGained + unWrap
            self.TotalCalsGainedLabel.text = "Total calories gained: \(TaskVariables.TotalCalNumGained)"
            self.view.endEditing(true)
        }
    }
    
    @IBAction func reset(_ sender: UIButton) {
    
    TaskVariables.TotalCalNumGained = 0
         self.TotalCalsGainedLabel.text = "Total calories gained: \(TaskVariables.TotalCalNumGained)"
    }
}
