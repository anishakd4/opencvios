//
//  ViewController.swift
//  OpenCVproject
//
//  Created by Anish Kumar Dubey on 03/08/19.
//  Copyright © 2019 Anish Kumar Dubey. All rights reserved.
//

import UIKit


class MyCell: UICollectionViewCell {
    @IBOutlet weak var cellImage: UIImageView!
    @IBOutlet weak var filterName: UILabel!
}

class ViewController: UIViewController, UICollectionViewDataSource, UICollectionViewDelegate {
    
    @IBOutlet weak var collectionView: UICollectionView!
    @IBOutlet weak var imageView: UIImageView!
    
    let filterNames = ["Cartoon", "Pencil Blend", "Pencil Edge", "XPROO", "Moon", "Kelvin", "Clarendon", "Canny", "Cooling", "Warming", "Brightify", "Diminify", "Hot Color Transfer", "Cool Color Transfer", "Desaturation", "Gray", "Postcard", "RetroFilter"]

    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return 18
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "cell", for: indexPath) as! MyCell
        cell.cellImage.image = UIImage(named: "image.jpg")
        cell.filterName.text = filterNames[indexPath.row]
        return cell
    }
    
    func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        let image = UIImage(named: "image.jpg")
        if indexPath.row == 0{
            let processedImage = OpenCVWrapper.cartoonFilter(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 1{
            let processedImage = OpenCVWrapper.pencilBlend(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 2{
            let processedImage = OpenCVWrapper.pencilEdge(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 3{
            let processedImage = OpenCVWrapper.xproFilter(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 4{
            let processedImage = OpenCVWrapper.moonFilter(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 5{
            let processedImage = OpenCVWrapper.kelvinFilter(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 6{
            let processedImage = OpenCVWrapper.clarendonFilter(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 7{
            let processedImage = OpenCVWrapper.cannyFilter(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 8{
            let processedImage = OpenCVWrapper.coolingFilter(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 9{
            let processedImage = OpenCVWrapper.warmingFilter(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 10{
            let processedImage = OpenCVWrapper.increaseBrightness(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 11{
            let processedImage = OpenCVWrapper.decreaseBrightness(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 12{
            let image1 = UIImage(named: "image1.jpg")
            let processedImage = OpenCVWrapper.colorTransfer(withOpenCV: image!, image1!)
            imageView.image = processedImage
        }else if indexPath.row == 13{
            let image1 = UIImage(named: "image2.jpg")
            let processedImage = OpenCVWrapper.colorTransfer(withOpenCV: image!, image1!)
            imageView.image = processedImage
        }else if indexPath.row == 14{
            let processedImage = OpenCVWrapper.desaturationFilter(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 15{
            let processedImage = OpenCVWrapper.grayImage(withOpenCV: image!)
            imageView.image = processedImage
        }else if indexPath.row == 16{
            let text = UIImage(named: "text.jpg")
            let texture = UIImage(named: "texture.jpg")
            let processedImage = OpenCVWrapper.postcardFilter(withOpenCV: image!, text!, texture!)
            imageView.image = processedImage
        }else if indexPath.row == 17{
            let fuzzyBorder = UIImage(named: "fuzzyBorder.png")
            let scratches = UIImage(named: "scratches.png")
            let processedImage = OpenCVWrapper.retroFilter(withOpenCV: image!, fuzzyBorder!, scratches!)
            imageView.image = processedImage
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        collectionView.dataSource = self
        collectionView.delegate = self
        let image = UIImage(named: "image.jpg")
        imageView.image = image
    }


}

